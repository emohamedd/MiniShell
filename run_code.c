/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_code.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 18:38:31 by haarab            #+#    #+#             */
/*   Updated: 2023/09/30 22:19:34 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, ("echo")) == 0 || ft_strcmp(cmd, ("cd")) == 0
		|| ft_strcmp(cmd, ("export")) == 0 || ft_strcmp(cmd, ("env")) == 0
		|| ft_strcmp(cmd, ("pwd")) == 0 || ft_strcmp(cmd, ("exit")) == 0
		|| ft_strcmp(cmd, ("unset")) == 0)
	{
		return (1);
	}
	return (0);
}

void	run_builtins(t_vars *vars, int i, char *cwd)
{
	if ((ft_strncmp("echo", vars->cmds[i].cmd, ft_strlen(vars->cmds[i].cmd)
				+ 1) == 0))
		run_echo(vars->cmds[i].cmds_args);
	else if (ft_strncmp("cd", vars->cmds[i].cmd, ft_strlen(vars->cmds[i].cmd)
			+ 1) == 0)
		run_cd(vars->cmds[i].cmds_args, vars, cwd);
	else if (ft_strncmp("pwd", vars->cmds[i].cmd, ft_strlen(vars->cmds[i].cmd)
			+ 1) == 0)
		run_pwd(cwd);
	else if (ft_strncmp("export", vars->cmds[i].cmd,
			ft_strlen(vars->cmds[i].cmd) + 1) == 0)
		run_export(vars, i);
	else if (ft_strncmp("env", vars->cmds[i].cmd, ft_strlen(vars->cmds[i].cmd)
			+ 1) == 0)
		env_cmd(vars);
	else if (ft_strncmp("unset", vars->cmds[i].cmd, ft_strlen(vars->cmds[i].cmd)
			+ 1) == 0)
		run_unset(vars, i);
	else if (ft_strncmp("exit", vars->cmds[i].cmd, ft_strlen(vars->cmds[i].cmd)
			+ 1) == 0)
		run_exit(vars, i);
}

void	cmd_builtins(t_vars *vars, int i)
{
	char	*cwd;

	cwd = getcwd(NULL, 1024);
	change_pwd(vars, cwd);
	run_builtins(vars, i, cwd);
	free(cwd);
}

void	run(char **args, t_vars *vars)
{
	int		i;
	int		status;
	pid_t	*childs;

	if (syntax_err(args))
		return ;
	fill_commands(args, vars);
	i = 0;
	childs = malloc_((sizeof(int) * vars->n_commandes), NULL, 0, NULL);
	while (i < vars->n_commandes)
	{
		if (is_builtin(vars->cmds[i].cmd))
			ft_builtins(vars, i, childs);
		else
			is_notbuiltins(vars, i, childs);
		i++;
	}
	i = -1;
	while (++i < vars->n_commandes)
	{
		waitpid(childs[i], &status, 0);
		i++;
	}
}
