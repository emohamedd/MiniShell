/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 18:35:50 by haarab            #+#    #+#             */
/*   Updated: 2023/09/30 22:47:21 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	childs_pipe(t_vars *vars, int i, int fd[2], int prev_fd)
{
	if (i == vars->n_commandes - 1)
	{
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
}

void	pipes_path(t_vars *vars, int i)
{
	ft_putstr_fd("minishell : ", 2);
	ft_putstr_fd(vars->cmds[i].cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	g_exit_status = 127;
	exit(g_exit_status);
}

void	cmd_execve(char *path, t_vars *vars, int i)
{
	execve(path, vars->cmds[i].cmds_args, vars->envp);
	ft_putstr_fd("minishell: No such file or directory\n", 2);
}

void	pipe_commands(t_vars *vars, int i, pid_t *childs)
{
	t_data	data;

	if (pipe(data.fd) == -1)
		return ;
	data.path = get_path(vars, vars->cmds[i].cmd);
	childs[i] = fork();
	if (childs[i] < 0)
		return ;
	else if (childs[i] == 0)
	{
		if (data.path == NULL)
			pipes_path(vars, i);
		childs_pipe(vars, i, data.fd, data.prev_fd);
		cmd_execve(data.path, vars, i);
	}
	else
	{
		if (i > 0)
			close(data.prev_fd);
		data.prev_fd = data.fd[0];
		close(data.fd[1]);
	}
}
