/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haarab <haarab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 20:46:34 by haarab            #+#    #+#             */
/*   Updated: 2023/09/30 20:47:59 by haarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_export(t_vars *vars, int i)
{
	int	k;

	if (!vars->cmds[i].cmds_args[1])
		export_cmd(vars, NULL);
	k = 1;
	while (vars->cmds[i].cmds_args[k])
	{
		export_cmd(vars, vars->cmds[i].cmds_args[k]);
		k++;
	}
}

void	run_unset(t_vars *vars, int i)
{
	int	k;

	k = 1;
	while (vars->cmds[i].cmds_args[k])
	{
		check_unset(vars->cmds[i].cmds_args, vars, k);
		k++;
	}
}

void	run_exit(t_vars *vars, int i)
{
	cmd_exit(vars->cmds[i].cmds_args);
	exit(exit_status);
}

void	run_pwd(char *cwd)
{
	printf("%s\n", cwd);
	exit_status = 0;
}
