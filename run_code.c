/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_code.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haarab <haarab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 18:38:31 by haarab            #+#    #+#             */
/*   Updated: 2023/09/18 13:02:03 by haarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void run(char *cmd, char **args, t_vars *vars, char *str)
{
	char *cwd = getcwd(NULL, 1024);
	
	if (ft_strncmp(cmd, "echo", ft_strlen("echo")) == 0)
	{
			if (args[1] != NULL && ft_strncmp(args[1], "$?", ft_strlen("$?")) == 0)
			{
				printf ("%d\n", vars->exit_status);
			}
			else
			{
				run_echo(args, vars);
			}
	}

	
    else if (ft_strncmp(cmd, "pwd", ft_strlen("pwd")) == 0)
    {
		printf("%s\n", cwd);
		vars->exit_status = 0;
    }

	else if (ft_strncmp(cmd, "export", ft_strlen("export")) == 0)
	{
		if (!args[1])
			export_cmd(vars, NULL, NULL);
		int i = 1;
		while (args[i])
		{
			export_cmd(vars, args[i], args);
			i++;
		}
	}
	
	else if (ft_strncmp(cmd, "env", ft_strlen("env")) == 0)
	{
		env_cmd(vars);
	}
	else if (ft_strncmp(cmd, "unset", ft_strlen("unset")) == 0)
	{
		int i = 1;
		while (args[i])
		{
			check_unset(args, vars, i);
			i++;
		}
		
	}
    else if (ft_strncmp(cmd, "exit", ft_strlen("exit")) == 0)
        exit (1);
	
	else
	{
		fill_commands(args, vars);
		pipe_red(vars);
	}
}