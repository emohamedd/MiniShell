/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haarab <haarab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 13:10:25 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/19 19:38:40 by haarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int c, char **v, char **env)
{
	char **str;
	t_vars vars;
	char **cmds;
	
	cmds = NULL;
	v += c;
	vars.exit_status = 0;
	vars.envp = env;
    vars.env = malloc(sizeof(t_env) * (count_argiment(vars.envp)));
    fell_env_struct(&vars);
	vars.env_number = count_argiment(vars.envp);
    char *input;
    t_info **tokens = NULL; 
	signal(SIGINT, sigintHandler);
    while(1)
    {
        input = read_input();
		if (input == NULL)
		{	
    		return (vars.exit_status);
		}
		char *trimed = ft_strtrim(input , " \t\r\n");
        if (trimed == NULL)
		{	
    		return (vars.exit_status);
		}
		if (!trimed[0])
		{
			continue;
		}
		str =  make_token(trimed);
		// 	int x = 0;
		// while (x < 8)
		// {
		// 	printf("***--[%s]--***\n", str[x]);
		// 	x++;
		// }
        // str = ft_split(trimed, ' ');
		if(str)
        {
			tokens = allocat_token(str, &vars);
			if(!tokens)
				continue;
			cmds = get_cmds(tokens);
			if (!cmds)
				return (0);
			// int x = 0;
			// while (x < 4)
			// {
			// 	printf("***%s\n", cmds[x]);
			// 	x++;
			// }
			syn_err(cmds, &vars);
			vars.count_argiment = lenght_of_the_2d(str);
			int fdin = dup(STDIN_FILENO);
			int fdou = dup(STDOUT_FILENO);
			run(tokens[0]->content, cmds, &vars, trimed);
			dup2(fdin, 0);
			dup2(fdou, 1);
			// table(cmds, tokens);
        }
    }
	
    return 0;
}
