/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_code.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haarab <haarab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 18:38:31 by haarab            #+#    #+#             */
/*   Updated: 2023/09/18 23:56:22 by haarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void run(char *cmd, char **args, t_vars *vars, char *str)
{
	char *cwd = getcwd(NULL, 1024);
	fill_commands(args, vars);
	int i = 0;
	while (i < vars->n_commandes)
	{
		if ((ft_strcmp("echo", vars->cmds[i].cmd) == 0))
		{
			if (vars->cmds[i].cmds_args[1] != NULL && ft_strcmp("$?", vars->cmds[i].cmds_args[1]) == 0)
			{
				printf ("%d\n", vars->exit_status);
			}
			else if (i == 0)
			{
				if (vars->n_commandes == 1)
					run_echo(vars->cmds[i].cmds_args, vars);
				else if (vars->n_commandes > 0)
				{
					pipe_red(vars, i);
				}
			}
		}
		else if (ft_strcmp("cd", vars->cmds[i].cmd) == 0)
    	{
			if (vars->n_commandes == 1)
			{
        		run_cd(vars->cmds[i].cmds_args, vars);
			}
			// else if (vars->n_commandes > 0)
			// 	pipe_red(vars, i);
    	}
		else if (ft_strcmp("pwd", vars->cmds[i].cmd) == 0)
		{
			if (!vars->cmds[i].has_redirections)
			{
				printf("%s\n", cwd);
				vars->exit_status = 0;
			}
			else if (vars->cmds[i].has_redirections)
				pipe_red(vars, i);
			while (vars->cmds[i].is_nex_pip && (ft_strcmp(vars->cmds[i].cmd, vars->cmds[i + 1].cmd) == 0))
			{
				i++;
			}
		}
		else if (ft_strcmp("export", vars->cmds[i].cmd) == 0)
		{
			if (vars->n_commandes == 1)
			{
				if (!vars->cmds[i].cmds_args[1])
					export_cmd(vars, NULL, NULL);
				int k = 1;
				while (args[k])
				{
					export_cmd(vars, vars->cmds[i].cmds_args[k], vars->cmds[i].cmds_args);
					k++;
				}
			}
			// else if (vars->n_commandes > 0)
			// {
			// 	pipe_red(vars, i);
			// }
		}
		else if (ft_strcmp("env", vars->cmds[i].cmd) == 0)
		{
			if (vars->n_commandes == 1)
				env_cmd(vars);
			else if (vars->n_commandes > 0)
			{
				pipe_red(vars, i);
			}
		}
		else if (ft_strcmp("unset", vars->cmds[i].cmd) == 0)
		{
			int k = 1;
			while (vars->cmds[i].cmds_args[k])
			{
				check_unset(vars->cmds[i].cmds_args, vars, k);
				k++;
			}
			
		}
		else if (ft_strcmp("exit", vars->cmds[i].cmd) == 0)
		{
			exit (vars->exit_status);
		}
		
		else if (vars->cmds[i].has_redirections || !vars->cmds[i].is_nex_pip || vars->cmds[i].is_nex_pip)
		{
			pipe_red(vars, i);
		}
		i++;
	}		
}