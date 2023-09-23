/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haarab <haarab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 18:35:50 by haarab            #+#    #+#             */
/*   Updated: 2023/09/23 07:15:44 by haarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void pipe_commands(t_vars *vars, int i, pid_t  *childs) 
{
	int status, fd[2], prev_fd;
	char *path = NULL;
	if (pipe(fd) == -1)
		return ;
	
	path = get_path(vars, vars->cmds[i].cmd);
	childs[i] = fork();
	if (childs[i] < 0)
		return ;
	else if (childs[i] == 0)
	{
		if (path == NULL)
		{
			ft_putstr_fd("minishell : ", 2);
			ft_putstr_fd(vars->cmds[0].cmd, 2);
			ft_putstr_fd(": command not found\n", 2);
			exit (127);
		}
		if (i == vars->n_commandes - 1) {
			dup2(prev_fd, 0);
		}
		else if (i == 0) 
		{
			dup2(fd[1], 1);
		}
		else 
		{
			dup2(prev_fd, 0);
			dup2(fd[1], 1);
		}
		close(fd[0]);
		close(fd[1]);
		if (i > 0)
			close(prev_fd);
		char **expand = expand_s_quotes(vars->cmds[i].cmds_args);
		path = get_path(vars, expand[0]);
		execve(path, expand, vars->envp);
	}
	else 
	{
		if (i > 0)
			close(prev_fd);
		prev_fd = fd[0];
		close(fd[1]);
	}
}
