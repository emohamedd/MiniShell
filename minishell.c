/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 13:10:25 by emohamed          #+#    #+#             */
/*   Updated: 2023/10/01 08:57:10 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_x_max(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	initialize_vars(t_vars *vars, char **env)
{
	vars->envp = env;
	vars->env = malloc(sizeof(t_env) * (count_argiment(vars->envp)));
	fell_env_struct(vars);
	vars->env_number = count_argiment(vars->envp);
}

int	run_shell_loop_helper(t_vars *vars, t_info **tokens, t_run runs)
{
	if (runs.str)
	{
		tokens = allocat_token(runs.str, vars);
		if (!tokens)
			return (0);
		runs.cmds = get_cmds(tokens);
		if (!runs.cmds)
			return (0);
		vars->count_argiment = lenght_of_the_2d(runs.str);
		runs.fdin = dup(STDIN_FILENO);
		runs.fdou = dup(STDOUT_FILENO);
		run(runs.cmds, vars);
		dup2(runs.fdin, 0);
		dup2(runs.fdou, 1);
		malloc_(0, NULL, 2, NULL);
	}
	if (runs.input)
		free(runs.input);
	return (1);
}

int	main(int ac __attribute__((unused)), char **av __attribute__((unused)),
		char **env)
{
	t_vars	vars;
	t_info	**tokens;
	t_run	runs;

	g_exit_status = 0;
	initialize_vars(&vars, env);
	tokens = NULL;
	rl_catch_signals = 0;
	signal(SIGINT, siginthandler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		runs.input = read_input();
		if (runs.input == NULL)
			return (g_exit_status);
		runs.trimed = ft_strtrim(runs.input, " \t\r\n");
		if (runs.trimed == NULL)
			return (g_exit_status);
		if (!runs.trimed[0])
			continue ;
		runs.str = make_token(runs.trimed);
		if (!run_shell_loop_helper(&vars, tokens, runs))
			return (0);
	}
	return (0);
}
