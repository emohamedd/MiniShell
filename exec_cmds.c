/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 18:37:07 by haarab            #+#    #+#             */
/*   Updated: 2023/09/23 12:46:54 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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


void exec_cmds(t_vars *vars, int i) 
{
	int id;
	// char **expand = expand_s_quotes(vars->cmds[i].cmds_args);
	char *path;
		// path = get_path(vars, expand[0]);
	char *exp = ft_strtrim(vars->cmds[i].cmd, "\'");
	path = get_path(vars, exp);
	// setup_redirs(red, vars);
	// printf(">>%s<<\n", path);
	id = fork();
	if (id == 0) 
	{
		// if (vars->here_fd)
		// {
		// 	dup2(vars->here_fd, 0);
		// 	close(vars->here_fd);
		// 	vars->here_fd = 0;
		// }
		if (path == NULL)
		{
			ft_putstr_fd("minishell : ", 2);
			ft_putstr_fd(exp, 2);
			ft_putstr_fd(": command not found\n", 2);
			exit(127);
		}
		// execve(path, expand, vars->envp);
		execve(path, vars->cmds[i].cmds_args, vars->envp);
		ft_putstr_fd("minishell: No such file or directory\n", 2);
		// perror("execve");
		exit(127);
	}
	wait(&vars->exit_status);
	vars->exit_status = WEXITSTATUS(vars->exit_status);
}