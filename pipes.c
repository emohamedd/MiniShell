/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haarab <haarab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 18:35:50 by haarab            #+#    #+#             */
/*   Updated: 2023/09/21 22:05:35 by haarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void pipe_commands(t_vars *vars, int i, pid_t  *childs) 
{
	int status, fd[2], prev_fd;
	char *path = NULL;
	if (pipe(fd) == -1)
		return ;
	
	childs[i] = fork();
	if (childs[i] < 0)
		return ;
	else if (childs[i] == 0) {
		if (i == vars->n_commandes - 1) {
			dup2(prev_fd, 0);
		}
		else if (i == 0) {
			dup2(fd[1], 1);
		}
		else {
			dup2(prev_fd, 0);
			dup2(fd[1], 1);
		}
		close(fd[0]);
		close(fd[1]);
		if (i > 0)
			close(prev_fd);
		path = get_path(vars, vars->cmds[i].cmd);
		execve(path, vars->cmds[i].cmds_args, vars->envp);
	}
	else {
		if (i > 0)
			close(prev_fd);
		prev_fd = fd[0];
		close(fd[1]);
	}
}