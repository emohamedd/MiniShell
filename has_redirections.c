/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haarab <haarab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 20:59:20 by haarab            #+#    #+#             */
/*   Updated: 2023/09/19 17:37:30 by haarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	has_redirections(t_vars *vars, int i)
{
	int j = 0;
	int fd = 0;
	if (vars->cmds[i].has_redirections)
	{
		while(vars->cmds[i].opera_derec[j])
		{
			if (!strcmp(vars->cmds[i].opera_derec[j], ">"))
			{
				fd = open(vars->cmds[i].file_derec[j], O_CREAT | O_TRUNC | O_RDWR, 0644);
				dup2(fd, 1);
				close(fd);
			}
			else if (!strcmp(vars->cmds[i].opera_derec[j], "<"))
			{
				fd = open(vars->cmds[i].file_derec[j],  O_RDWR);
				dup2(fd, 0);
				close(fd);

			}
			else if (!strcmp(vars->cmds[i].opera_derec[j], ">>")) {
				fd = open(vars->cmds[i].file_derec[j], O_CREAT | O_APPEND | O_RDWR, 0644);
				dup2(fd, 1);
				close(fd);

			}
			j++;
		}	
	}
}