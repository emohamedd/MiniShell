/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haarab <haarab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 18:37:07 by haarab            #+#    #+#             */
/*   Updated: 2023/09/30 20:07:44 by haarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path(t_vars *vars, char *cmd)
{
	struct stat	file_info;
	char		**path;
	char		*res;
	char		*temper1;
	char		*fullcmd;

	vars->i = 0;
	if (ft_strchr(cmd, '/'))
		return (cmd);
	res = ft_getenv("PATH", vars);
	if (res == NULL)
		return (NULL);
	path = ft_split(res, ':');
	while (path[vars->i])
	{
		temper1 = ft_strjoin(path[vars->i], "/");
		fullcmd = ft_strjoin(temper1, cmd);
		if (stat(fullcmd, &file_info) == 0)
			return (fullcmd);
		vars->i++;
	}
	return (NULL);
}

void	comande_exec(t_vars *vars, int i, char *path, char *exp)
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

void	exec_cmds(t_vars *vars, int i)
{
	int		id;
	char	*path;
	char	*exp;

	exp = ft_strtrim(vars->cmds[i].cmd, "\'");
	path = get_path(vars, exp);
	id = fork();
	if (id == 0)
	{
		comande_exec(vars, i, path, exp);
	}
	waitpid(id, &exit_status, 0);
	exit_status = WEXITSTATUS(exit_status);
}
