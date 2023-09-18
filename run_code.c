/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_code.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 18:38:31 by haarab            #+#    #+#             */
/*   Updated: 2023/09/18 10:10:41 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void run(char *cmd, char **args, t_vars *vars, char *str)
{
	char *cwd = getcwd(NULL, 1024);
	

    if (ft_strncmp(cmd, "echo", ft_strlen("echo")) == 0)
    {
		if (ft_strncmp(args[1], "$?", ft_strlen("$?")) == 0)
		{
			printf ("%d\n", vars->exit_status);
		}
		// printf ("%s\n", args[1]);
		else
        	run_echo(args, vars);
    }
	
	 else if (ft_strncmp(cmd, "cd", ft_strlen("cd")) == 0)
    {
        run_cd(args, vars);
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
		int i = 0;
		while(i < vars->n_commandes)
		{
			int j = 0;
			int fd = 0;
			if (vars->cmds[i].is_nex_pip)
		 	{ 
		 		pipe_commands(vars, i);
			}
			if (vars->cmds[i].has_redirections)
			{
				while(vars->cmds[i].opera_derec[j])
				{
					if (!strcmp(vars->cmds[i].opera_derec[j], ">"))
					{
							fd = open(vars->cmds[i].file_derec[j], O_CREAT | O_TRUNC | O_RDWR, 0644);
							dup2(fd, 1);
					}
					else if (!strcmp(vars->cmds[i].opera_derec[j], "<"))
					{
						fd = open(vars->cmds[i].file_derec[j],  O_RDWR);
						dup2(fd, 0);
					}else if (!strcmp(vars->cmds[i].opera_derec[j], ">>")) {
							fd = open(vars->cmds[i].file_derec[j], O_CREAT | O_APPEND | O_RDWR, 0644);
							dup2(fd, 1);
					}
					j++;
				}	
			}
			if (!vars->cmds[i].is_nex_pip)
				exec_cmds(vars, i);
			i++;
		}
	}
}