/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 18:44:19 by haarab            #+#    #+#             */
/*   Updated: 2023/10/01 00:43:43 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtins_pipes(t_vars *vars, int i, pid_t *childs)
{
	int	fd[2];

	pipe(fd);
	childs[i] = fork();
	if (childs[i] == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		cmd_builtins(vars, i);
		close(fd[1]);
		exit(0);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], 0);
		wait(&childs[i]);
		close(fd[0]);
	}
}

void	ft_builtins(t_vars *vars, int i, pid_t *childs)
{
	if (vars->cmds[i].has_redirections)
		if (has_redirections(vars, i) == 1)
			return ;
	if (vars->cmds[i].is_nex_pip)
	{
		builtins_pipes(vars, i, childs);
	}
	else
	{
		cmd_builtins(vars, i);
	}
}

void	is_notbuiltins(t_vars *vars, int i, pid_t *childs)
{
	if (vars->cmds[i].has_redirections)
	{
		if (has_redirections(vars, i) == 1)
			return ;
	}
	if (vars->n_commandes > 1)
	{
		pipe_commands(vars, i, childs);
	}
	else if (vars->n_commandes == 1 && i == 0)
	{
		exec_cmds(vars, i);
	}
}
