/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_code.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 18:38:31 by haarab            #+#    #+#             */
/*   Updated: 2023/09/30 01:53:10 by emohamed         ###   ########.fr       */
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

void run_export(t_vars *vars, int i)
{
	int k;

	if (!vars->cmds[i].cmds_args[1])
		export_cmd(vars, NULL, NULL);
	k = 1;
	while (vars->cmds[i].cmds_args[k])
	{
		export_cmd(vars, vars->cmds[i].cmds_args[k],
			vars->cmds[i].cmds_args);
		k++;
	}
}

void run_unset(t_vars *vars, int i)
{
	int k;

	k = 1;
	while (vars->cmds[i].cmds_args[k])
	{
		check_unset(vars->cmds[i].cmds_args, vars, k);
		k++;
	}
}

void run_exit(t_vars *vars, int i)
{
	
	cmd_exit(vars->cmds[i].cmds_args, vars);
	exit(exit_status);
}

void run_pwd(t_vars *vars, char *cwd)
{
	printf("%s\n", cwd);
	exit_status = 0;
}

void	run_builtins(t_vars *vars, int i, char *cwd)
{
	if ((ft_strncmp("echo", vars->cmds[i].cmd, ft_strlen(vars->cmds[i].cmd)
				+ 1) == 0))
		run_echo(vars->cmds[i].cmds_args, vars);
	else if (ft_strncmp("cd", vars->cmds[i].cmd, ft_strlen(vars->cmds[i].cmd)
			+ 1) == 0)
		run_cd(vars->cmds[i].cmds_args, vars, cwd);
	else if (ft_strncmp("pwd", vars->cmds[i].cmd, ft_strlen(vars->cmds[i].cmd)
			+ 1) == 0)
		run_pwd(vars, cwd);
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

int ft_error(char **str)
{
	int i = 0;
	while (str[i])
	{
		int j = 0;
		int a = 0;
		int b = 0;
		while (str[i][j])
		{
			if (str[i][j] == '<')
				a++;
			if (str[i][j] == '>')
				b++;
			j++;
		}
		if (a > 2 || b > 2)
			return (1);
		i++;
	}
	return 0;
}

// int ft_error(char **str)
// {
// 	int i = 0;
// 	while (str[i])
// 	{
// 		int j = 0;
// 		int a = 0;
// 		int b = 0;
// 		while (str[i][j])
// 		{
// 			if (str[i][j] == '<')
// 				a++;
// 			if (str[i][j] == '>')
// 				b++;
// 			j++;
// 		}
// 		if (a > 2 || b > 2 || c % 2 != 0 || d % 2 != 0)
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

int syntax_errors(char **args, t_vars *vars)
{
	int count = 0;
	
	if (ft_error(args))
		return (1);
	int i = 0;
	int j = 0;
	while (args[i])
	{
		if (!ft_strncmp("|", args[i], ft_strlen(args[i])) && args[i + 1] == NULL)
			j++;
		if (!ft_strncmp(">", args[i], ft_strlen(args[i])) && args[i + 1] == NULL)
			j++;
		if (!ft_strncmp("<", args[i], ft_strlen(args[i])) && args[i + 1] == NULL)
			j++;
		if (!ft_strncmp("<<", args[i], ft_strlen(args[i])) && args[i + 1] == NULL)
			j++;
		else if (!ft_strncmp(">>", args[i], ft_strlen(args[i])) && args[i + 1] == NULL)
			j++;
		if (!ft_strncmp("|", args[i], ft_strlen(args[i])) && (!ft_strncmp("|", args[i + 1], ft_strlen(args[i + 1]))))
			j++;
		if (!ft_strncmp(">>", args[i], ft_strlen(args[i])) && (!ft_strncmp("|", args[i + 1], ft_strlen(args[i + 1]))))
			j++;
		if (!ft_strncmp("<<", args[i], ft_strlen(args[i])) && (!ft_strncmp("|", args[i + 1], ft_strlen(args[i + 1]))))
			j++;
		if (!ft_strncmp("|", args[0], ft_strlen(args[0]) + 1))
			j++;
		i++;
	}
	return (j);
}

void 	run(char *cmd, char **args, t_vars *vars, char **str)
{
	// if (syntax_err(args, vars))
	// 	return ;
	fill_commands(args, vars);
	int i = 0;
	int status;
	pid_t *childs = malloc_((sizeof(int) * vars->n_commandes), NULL, 0, NULL);
	
	// pid_t *childs = malloc_((sizeof(int) * vars->n_commandes), NULL, 0, NULL);
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
