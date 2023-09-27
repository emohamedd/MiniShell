/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 13:10:25 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/27 18:24:17 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int c, char **v, char **env)
{
	char	**str;
	t_vars	vars;
	char	**cmds;
	char	*input;
	t_info	**tokens;
	char	*trimed;
	int		fdin;
	int		fdou;

	cmds = NULL;
	v += c;
	exit_status = 0;
	vars.envp = env;
	vars.env = malloc(sizeof(t_env) * (count_argiment(vars.envp)));
	// vars.env = ft_malloc((sizeof(t_env) * (count_argiment(vars.envp))), NULL, 0, NULL);
	fell_env_struct(&vars);
	vars.env_number = count_argiment(vars.envp);
	tokens = NULL;
	// rl_catch_signals = 0;
	signal(SIGINT, siginthandler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		input = read_input();
		if (input == NULL)
		{
			return (exit_status);
		}
		trimed = ft_strtrim(input, " \t\r\n");
		if (trimed == NULL)
		{
			return (exit_status);
		}
		if (!trimed[0])
		{
			continue ;
		}
		// syn_err(str, &vars);
		str = make_token(trimed);
		// rl_catch_signals = 0;
		if (str)
		{
			tokens = allocat_token(str, &vars);
			if (!tokens)
				continue ;
			cmds = get_cmds(tokens);
			if (!cmds)
				return (0);
			vars.count_argiment = lenght_of_the_2d(str);
			fdin = dup(STDIN_FILENO);
			fdou = dup(STDOUT_FILENO);
			run(tokens[0]->content, cmds, &vars, str);
			dup2(fdin, 0);
			dup2(fdou, 1);
			// table(cmds, tokens);
			ft_malloc(0, NULL, 2, NULL);
		}
	}
	return (0);
}
