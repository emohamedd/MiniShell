/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 18:35:50 by haarab            #+#    #+#             */
/*   Updated: 2023/09/25 15:50:24 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_commands(t_vars *vars, int i, pid_t *childs)
{
	int		status, fd[2], prev_fd;
	char	*path;

	path = NULL;
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
			ft_putstr_fd(vars->cmds[i].cmd, 2);
			ft_putstr_fd(": command not found\n", 2);
			exit(127);
		}
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
		execve(path, vars->cmds[i].cmds_args, vars->envp);
		ft_putstr_fd("minishell: No such file or directory\n", 2);
	}
	else
	{
		if (i > 0)
			close(prev_fd);
		prev_fd = fd[0];
		close(fd[1]);
	}
}
