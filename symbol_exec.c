/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:13:31 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/18 12:15:07 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void pipe_red(t_vars *vars)
{
    int i = 0;
		while(i < vars->n_commandes)
		{
			int j = 0;
			int fd = 0;
			if (vars->cmds[i].is_nex_pip)
		 	{ 
		 		pipe_commands(vars, i);
			}
			if (vars->cmds[i].has_redirections)
			{
				while(vars->cmds[i].opera_derec[j])
				{
					if (!strcmp(vars->cmds[i].opera_derec[j], ">"))
					{
							fd = open(vars->cmds[i].file_derec[j], O_CREAT | O_TRUNC | O_RDWR, 0644);
							dup2(fd, 1);
					}
					else if (!strcmp(vars->cmds[i].opera_derec[j], "<"))
					{
						fd = open(vars->cmds[i].file_derec[j],  O_RDWR);
						dup2(fd, 0);
					}else if (!strcmp(vars->cmds[i].opera_derec[j], ">>")) {
							fd = open(vars->cmds[i].file_derec[j], O_CREAT | O_APPEND | O_RDWR, 0644);
							dup2(fd, 1);
					}
					j++;
				}	
			}
			if (!vars->cmds[i].is_nex_pip)
				exec_cmds(vars, i);
			i++;
		}
}