/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haarab <haarab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:13:31 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/19 19:45:27 by haarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void pipe_red(t_vars *vars, int i)
{

	if (vars->cmds[i].is_nex_pip && vars->cmds[i].has_redirections)
	{
		has_redirections(vars, i);
		pipe_commands(vars, i);
	}
	else if (vars->cmds[i].has_redirections && !vars->cmds[i].is_nex_pip)
	{
		has_redirections(vars, i);
		exec_cmds(vars, i);
	}
	else if (vars->cmds[i].is_nex_pip)
	{
		pipe_commands(vars, i);
	}
	else if (vars->cmds[i].has_redirections)
	{
		has_redirections(vars, i);
	}
	else if (!vars->cmds[i].is_nex_pip)
	{
		exec_cmds(vars, i);
		// if (vars->cmds[i].cmds_args[1] != NULL && ft_strcmp("$?", vars->cmds[i].cmds_args[1]) == 0)
		// {
		// 	printf ("%d\n", vars->exit_status);
		// }
	}
}