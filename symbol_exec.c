/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haarab <haarab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:13:31 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/21 22:01:56 by haarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void pipe_red(t_vars *vars, int i, pid_t *childs)
{
	if (vars->cmds[i].is_nex_pip)
	{
		pipe_commands(vars, i, childs);
		
	// 	// int fdin = dup(STDIN_FILENO);
	// 	// int fdou = dup(STDOUT_FILENO);
	// 	pipe_commands(vars, i, childs);
	// 	// dup2(fdin, 0);
	// 	// dup2(fdou, 1);
	// 	// close(fdin);
	// 	// close (fdou);
	// }
	}
}
// 	else if (!vars->cmds[i].is_nex_pip)
// 	{
// 		exec_cmds(vars, i);
// 	}
// }
