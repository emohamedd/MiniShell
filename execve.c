/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haarab <haarab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 18:33:23 by haarab            #+#    #+#             */
/*   Updated: 2023/09/12 20:33:23 by haarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_getenv(char *key, t_vars *vars)
{
	int i;

	i = 0;
	while (i < vars->env_number) {
		if (!ft_strncmp(vars->env[i].key, key, ft_strlen(key))) {
			return (vars->env[i].value);
		}
		i++;
	}
	return NULL;
}

char *get_path(t_vars *vars, char *cmd)
{
	int i = 0;
	char **path;
	char *res;
	
	if (ft_strchr(cmd, '/')) 
		return cmd;
	res = ft_getenv("PATH", vars);
	if(res == NULL)
		return (NULL);
	char *fullCmd;
	path = ft_split(res, ':');
	struct stat file_info;
	while (path[i]) {
		fullCmd = ft_strjoin(ft_strjoin(path[i], "/"), cmd);
		if (stat(fullCmd, &file_info) == 0) {
			return fullCmd;
		}
		i++;
	}
	return (NULL);
}


void exec_cmds(t_vars *vars, char *cmd, char **args)
{
	int id;
	char *path;
	path = get_path(vars, cmd);

	id = fork();
	if (id == 0) 
	{
		if (path == NULL)
		{
			ft_putstr_fd("minishell : ", 2);
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": command not found\n", 2);
			exit(127);
			
		}
		else if (execve(path, args, vars->envp) == -1)
		{
			perror("execve");
			exit(126);
		}
	}
	wait(&vars->exit_status);
	vars->exit_status = WEXITSTATUS(vars->exit_status);
}