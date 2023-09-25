/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_code.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haarab <haarab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 18:38:31 by haarab            #+#    #+#             */
/*   Updated: 2023/09/25 20:50:02 by haarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (ft_strcmp("echo", cmd) == 0 || ft_strcmp("cd", cmd) == 0
		|| ft_strcmp("export", cmd) == 0 || ft_strcmp("env", cmd) == 0
		|| ft_strcmp("pwd", cmd) == 0 || ft_strcmp("exit", cmd) == 0
		|| ft_strcmp("unset", cmd) == 0)
	{
		return (1);
	}
	return (0);
}

void	cmd_builtins(t_vars *vars, int i, char **str)
{
	char	*cwd;
	int		k;

	cwd = getcwd(NULL, 1024);
	if ((ft_strncmp("echo", vars->cmds[i].cmd, ft_strlen(vars->cmds[i].cmd)
				+ 1) == 0))
	{
		run_echo(vars->cmds[i].cmds_args, vars);
	}
	else if (ft_strncmp("cd", vars->cmds[i].cmd, ft_strlen(vars->cmds[i].cmd)
			+ 1) == 0)
	{
		run_cd(vars->cmds[i].cmds_args, vars);
	}
	else if (ft_strncmp("pwd", vars->cmds[i].cmd, ft_strlen(vars->cmds[i].cmd)
			+ 1) == 0)
	{
		printf("%s\n", cwd);
		vars->exit_status = 0;
	}
	else if (ft_strncmp("export", vars->cmds[i].cmd,
			ft_strlen(vars->cmds[i].cmd) + 1) == 0)
	{
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
	else if (ft_strncmp("env", vars->cmds[i].cmd, ft_strlen(vars->cmds[i].cmd)
			+ 1) == 0)
	{
		env_cmd(vars);
	}
	else if (ft_strncmp("unset", vars->cmds[i].cmd, ft_strlen(vars->cmds[i].cmd)
			+ 1) == 0)
	{
		k = 1;
		while (vars->cmds[i].cmds_args[k])
		{
			check_unset(vars->cmds[i].cmds_args, vars, k);
			k++;
		}
	}
	else if (ft_strncmp("exit", vars->cmds[i].cmd, ft_strlen(vars->cmds[i].cmd)
			+ 1) == 0)
	{
		cmd_exit(vars->cmds[i].cmds_args, vars);
		exit(vars->exit_status);
	}
}

int	ft_error(char **str)
{
	int	i;
	int	j;
	int	a;
	int	b;
	int	c;
	int	d;
	int	e;
	int	f;
	int	h;

	i = 0;
	while (str[i])
	{
		int j = 0;
		int a = 0;
		int b = 0;
		int c = 0;
		int d = 0;
		while (str[i][j])
		{
			if (str[i][j] == '<')
				a++;
			if (str[i][j] == '>')
				b++;
			if (str[i][j] == 39)
				c++;
			if (str[i][j] == 34)
				d++;
			j++;
		}
		if (a > 2 || b > 2 || c % 2 != 0 || d % 2 != 0)
			return (1);
		i++;
	}
	return (0);
}

int	syntax_errors(char **args, t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (ft_error(args))
		return (1);
	while (args[i])
	{
		if (!ft_strncmp("|", args[i], ft_strlen(args[i])) && (!ft_strncmp("<",
					args[i + 1], ft_strlen(args[i + 1]))))
			j++;
		if (!ft_strncmp("|", args[i], ft_strlen(args[i])) && (!ft_strncmp("|", args[i + 1], ft_strlen(args[i + 1]))))
			j++;
		if (!ft_strncmp("|", args[i], ft_strlen(args[i])) && (!ft_strncmp(">", args[i + 1], ft_strlen(args[i + 1]))))
			j++;
		if (!ft_strncmp("|", args[i], ft_strlen(args[i])) && (!ft_strncmp("<<",
					args[i + 1], ft_strlen(args[i + 1]))))
			j++;
		if (!ft_strncmp("|", args[i], ft_strlen(args[i])) && (!ft_strncmp(">>",
					args[i + 1], ft_strlen(args[i + 1]))))
			j++;
		if (!ft_strncmp("<", args[i], ft_strlen(args[i])) && (!ft_strncmp("|",
					args[i + 1], ft_strlen(args[i + 1]))))
			j++;
		if (!ft_strncmp(">", args[i], ft_strlen(args[i])) && (!ft_strncmp("|",
					args[i + 1], ft_strlen(args[i + 1]))))
			j++;
		if (!ft_strncmp(">", args[i], ft_strlen(args[i])) && (!ft_strncmp("<",
					args[i + 1], ft_strlen(args[i + 1]))))
			j++;
		if (!ft_strncmp("<", args[i], ft_strlen(args[i])) && (!ft_strncmp(">",
					args[i + 1], ft_strlen(args[i + 1]))))
			j++;
		if (!ft_strncmp("<<", args[i], ft_strlen(args[i])) && (!ft_strncmp("|",
					args[i + 1], ft_strlen(args[i + 1]))))
			j++;
		if (!ft_strncmp(">>", args[i], ft_strlen(args[i])) && (!ft_strncmp("|", args[i + 1], ft_strlen(args[i + 1]))))
			j++;
		if (!ft_strncmp("|", args[0], ft_strlen(args[0])) && args[1] != NULL)
			j++;
		i++;
	}
	return (j);
}

int	command_notfound(char **args, t_vars *vars)
{
	int i = 0;
	int j = 0;
	while (args[i])
	{
		if (!ft_strncmp("''", args[0], ft_strlen(args[0])) && (!ft_strncmp("|", args[1], ft_strlen(args[1]))))
			j++;
		if (!ft_strncmp("""", args[0], ft_strlen(args[0])) && (!ft_strncmp("|", args[1], ft_strlen(args[1]))))
			j++;
		i++;
	}
	return (j);
}


void 	run(char *cmd, char **args, t_vars *vars, char **str)
{
	if (syntax_errors(args, vars))
		return ;
	fill_commands(args, vars);
	int i = 0;
	int status;
	pid_t *childs = malloc(sizeof(int) * vars->n_commandes);
	while (i < vars->n_commandes)
	{
		if (is_builtin(vars->cmds[i].cmd))
		{
			ft_builtins(vars, i, str, childs);
		}
		else
		{
			is_notbuiltins(vars, i, childs);
		}
		i++;
	}
	i = -1;
	while (i < vars->n_commandes)
	{
		waitpid(childs[i], &status, 0);
		i++;
	}
}
