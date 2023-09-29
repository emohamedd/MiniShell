/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haarab <haarab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 18:37:07 by haarab            #+#    #+#             */
/*   Updated: 2023/09/29 20:52:14 by haarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char *get_path(t_vars *vars, char *cmd)
{
	int i = 0;
	char **path;
	char *res;
	char *temper1;
	
	if (ft_strchr(cmd, '/')) 
		return (cmd);
	res = ft_getenv("PATH", vars);
	if(res == NULL)
		return (NULL);
	char *fullCmd;
	path = ft_split(res, ':');
	struct stat file_info;
	while (path[i])
	{
		temper1 = ft_strjoin(path[i], "/");
		fullCmd = ft_strjoin(temper1, cmd);
		if (stat(fullCmd, &file_info) == 0) {
			return (fullCmd);
		}
		i++;
	}
	return (NULL);
}


void comande_exec(t_vars *vars, int i, char *path, char *exp)
{
	if (vars->here_fd)
	{
		dup2(vars->here_fd, 0);
		close(vars->here_fd);
		vars->here_fd = 0;
	}
	if (path == NULL && !vars->cmds[i].has_redirections)
	{
		ft_putstr_fd("minishell : ", 2);
		ft_putstr_fd(exp, 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	if (!execve(path, vars->cmds[i].cmds_args, vars->envp))
	{
		ft_putstr_fd("minishell: No such file or directory\n", 2);
		exit(127);
	}
}

void exec_cmds(t_vars *vars, int i) 
{
	int id;
	char *path;
	char *exp = ft_strtrim(vars->cmds[i].cmd, "\'");
	path = get_path(vars, exp);
	id = fork();
	if (id == 0) 
	{
		comande_exec(vars, i, path, exp);
	}
	// free(path);
	waitpid(id, &exit_status, 0);
	exit_status = WEXITSTATUS(exit_status);
}





// char *get_path(t_vars *vars, char *cmd)
// {
// 	int i = 0;
// 	char **path;
// 	char *res;
	
// 	if (ft_strchr(cmd, '/')) 
// 		return cmd;
// 	res = ft_getenv("PATH", vars);
// 	if(res == NULL)
// 		return (NULL);
// 	char *fullCmd;
// 	path = ft_split(res, ':');
// 	struct stat file_info;
// 	while (path[i]) {
// 		fullCmd = ft_strjoin(ft_strjoin(path[i], "/"), cmd);
// 		if (stat(fullCmd, &file_info) == 0) {
// 			return fullCmd;
// 		}
// 		i++;
// 	}
// 	return (NULL);
// }


// void exec_cmds(t_vars *vars, int i) 
// {
// 	int id;
// 	// char **expand = expand_s_quotes(vars->cmds[i].cmds_args);
// 	char *path;
// 		// path = get_path(vars, expand[0]);
// 	char *exp = ft_strtrim(vars->cmds[i].cmd, "\'");
// 	path = get_path(vars, exp);
// 	id = fork();
// 	if (id == 0) 
// 	{
// 		if (vars->here_fd)
// 		{
// 			dup2(vars->here_fd, 0);
// 			close(vars->here_fd);
// 			vars->here_fd = 0;
// 		}
// 		// execve(path, expand, vars->envp);
// 		if (path == NULL  && !vars->cmds[i].has_redirections)
// 		{
// 			ft_putstr_fd("minishell : ", 2);
// 			ft_putstr_fd(exp, 2);
// 			ft_putstr_fd(": command not found\n", 2);
// 			exit(127);
// 		}
// 		execve(path, vars->cmds[i].cmds_args, vars->envp);
// 		ft_putstr_fd("minishell: No such file or directory\n", 2);
// 		// perror("execve");
// 		exit(127);
// 	}
// 	exit_status = WEXITSTATUS(exit_status);
// }