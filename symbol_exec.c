/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haarab <haarab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:13:31 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/18 21:56:30 by haarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void pipe_red(t_vars *vars, int i)
{
	if (vars->cmds[i].is_nex_pip)
	{
		pipe_commands(vars, i);
	}
	if (vars->cmds[i].has_redirections)
	{
		has_redirections(vars, i);
	}
	if (!vars->cmds[i].is_nex_pip)
		exec_cmds(vars, i);
}