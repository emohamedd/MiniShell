/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_code.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 18:38:31 by haarab            #+#    #+#             */
/*   Updated: 2023/09/25 12:09:50 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_builtin(char *cmd) 
{
	if (ft_strcmp("echo", cmd) == 0 || ft_strcmp("cd", cmd) == 0  || ft_strcmp("export", cmd) == 0
		|| ft_strcmp("env", cmd) == 0 || ft_strcmp("pwd", cmd) == 0 || ft_strcmp("exit", cmd) == 0
			|| ft_strcmp("unset", cmd) == 0)
	{
		return 1;
	}
	return 0;
}

void cmd_builtins(t_vars *vars, int i, char **str)
{
	char *cwd = getcwd(NULL, 1024);
	if ((ft_strncmp("echo", vars->cmds[i].cmd, ft_strlen(vars->cmds[i].cmd) + 1) == 0))
	{
		run_echo(vars->cmds[i].cmds_args, vars);
	}
	else if (ft_strncmp("cd", vars->cmds[i].cmd, ft_strlen(vars->cmds[i].cmd) + 1) == 0)
	{
		run_cd(vars->cmds[i].cmds_args, vars);
	}
	else if (ft_strncmp("pwd", vars->cmds[i].cmd, ft_strlen(vars->cmds[i].cmd) + 1) == 0)
	{
		printf("%s\n", cwd);
		vars->exit_status = 0;
	}
	else if (ft_strncmp("export", vars->cmds[i].cmd, ft_strlen(vars->cmds[i].cmd) + 1) == 0)
	{
		if (!vars->cmds[i].cmds_args[1])
			export_cmd(vars, NULL, NULL);
		int k = 1;
		while (vars->cmds[i].cmds_args[k])
		{
			export_cmd(vars, vars->cmds[i].cmds_args[k], vars->cmds[i].cmds_args);
			k++;
		}
	}
	else if (ft_strncmp("env", vars->cmds[i].cmd, ft_strlen(vars->cmds[i].cmd) + 1) == 0)
	{
		env_cmd(vars);
	}
	else if (ft_strncmp("unset", vars->cmds[i].cmd, ft_strlen(vars->cmds[i].cmd) + 1) == 0)
	{
		int k = 1;
		while (vars->cmds[i].cmds_args[k])
		{
			check_unset(vars->cmds[i].cmds_args, vars, k);
			k++;
		}
	}
	else if (ft_strncmp("exit", vars->cmds[i].cmd, ft_strlen(vars->cmds[i].cmd) + 1) == 0)
	{
		cmd_exit(vars->cmds[i].cmds_args, vars);
		exit (vars->exit_status);
	}
}

int ft_error(char **str)
{
	int i = 0;
	while (str[i])
	{
		int j = 0;
		int a = 0;
		int b = 0;
		int c = 0;
		int d = 0;
		int e = 0;
		int f = 0;
		int h = 0;
		while (str[i][j])
		{
			if (str[i][j] == '<')
				a++;
			if (str[i][j] == '>')
				b++;
			if (str[i][j] == '|')
				c++;
			if (str[i][j] == '|' || str[i][j] == '<')
				d++;
			if (str[i][j] == '|' || str[i][j] == '>')
				e++;
			j++;
		}
		if (a > 2 || b > 2 || c > 1 || d > 1 || e > 1 || f > 1)
			return (1);
		i++;
	}
	return (0);
}



int syntax_errors(char **args, t_vars *vars)
{
	int i = 0;
	int j = 0;

	if (ft_error(args))
		return (1);
	while (args[i])
	{
		if (!ft_strncmp("|", args[i], ft_strlen(args[i])) && (!ft_strncmp("<", args[i + 1], ft_strlen(args[i + 1]))))
			j++;
		if (!ft_strncmp("|", args[i], ft_strlen(args[i])) && (!ft_strncmp(">", args[i + 1], ft_strlen(args[i + 1]))))
			j++;
		if (!ft_strncmp("|", args[i], ft_strlen(args[i])) && (!ft_strncmp("<<", args[i + 1], ft_strlen(args[i + 1]))))
			j++;
		if (!ft_strncmp("|", args[i], ft_strlen(args[i])) && (!ft_strncmp(">>", args[i + 1], ft_strlen(args[i + 1]))))
			j++;
		if (!ft_strncmp("<", args[i], ft_strlen(args[i])) && (!ft_strncmp("|", args[i + 1], ft_strlen(args[i + 1]))))
			j++;
		if (!ft_strncmp(">", args[i], ft_strlen(args[i])) && (!ft_strncmp("|", args[i + 1], ft_strlen(args[i + 1]))))
			j++;
		if (!ft_strncmp(">", args[i], ft_strlen(args[i])) && (!ft_strncmp("<", args[i + 1], ft_strlen(args[i + 1]))))
			j++;
		if (!ft_strncmp("<", args[i], ft_strlen(args[i])) && (!ft_strncmp(">", args[i + 1], ft_strlen(args[i + 1]))))
			j++;
		if (!ft_strncmp("<<", args[i], ft_strlen(args[i])) && (!ft_strncmp("|", args[i + 1], ft_strlen(args[i + 1]))))
			j++;
		if (!ft_strncmp("|", args[i], ft_strlen(args[i])) && args[i + 1] == NULL)
			j++;
		if (!ft_strncmp("|", args[0], ft_strlen(args[0])))
			j++;
		i++;
	}
	return (j);	
}

void 	run(char *cmd, char **args, t_vars *vars, char **str)
{
	fill_commands(args, vars);
	// if (syntax_errors(args, vars) > 0)
	// {
	// 	printf ("minishell: syntax error\n");
	// 	vars->exit_status = 2;
	// 	return;
	// }
	int i = 0;
	int status;
	pid_t *childs = malloc(sizeof(int) * vars->n_commandes);
	while (i < vars->n_commandes)
	{
		if (is_builtin(vars->cmds[i].cmd))
		{
			if (vars->cmds[i].has_redirections)
			{
				if (has_redirections(vars, i))
					return ;
			}
			if (vars->cmds[i].is_nex_pip)
			{
				int fd[2];
				// int id;
				pipe(fd);
				childs[i] = fork();
				if (childs[i] == 0)
				{
					dup2(fd[1], 1);
					close(fd[0]);
					close(fd[1]);					
					cmd_builtins(vars, i, str);
					exit(0);
				}
				else
				{
					close(fd[1]);
					dup2(fd[0], 0);
					close(fd[0]);
				}
				wait(&childs[i]);
			}
			else 
			{
				cmd_builtins(vars, i, str);
			}
		}
		else 
		{
			if (vars->cmds[i].has_redirections)
			{
				if (has_redirections(vars, i))
					return ;
			}
			if (vars->n_commandes > 1)
			{
				while (i < vars->n_commandes)
				{
					pipe_commands(vars, i, childs);
					i++;
				}
			}
			if (vars->n_commandes == 1 && i == 0)
			{
				exec_cmds(vars, i);
			}
		}
		i++;
	}
	
	// if (vars->n_commandes > 1)
	// {
		i = -1;
		while (i < vars->n_commandes)
		{
			// vars->exit_status = WEXITSTATUS(vars->exit_status);
			waitpid(childs[i], &status, 0);
			i++;
		}
	// }
}
