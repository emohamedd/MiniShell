/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haarab <haarab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 15:31:58 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/07 20:10:59 by haarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H


#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include "libft/libft.h"
#include <sys/wait.h>

typedef struct s_env
{
    char *key;
    int  is_equal;
    char *value;
} t_env;


typedef struct s_vars
{
	int	count_argiment;
	int env_number;
	char **envp;
	char *strarg;
	char *strvalue;
    t_env *env;
}	t_vars;

    void	display_prompt();
    char	*read_input();
    char	**ft_split(char const *s, char c);
	void 	run(char *cmd, char **args, t_vars *vars);
	void 	fell_env_struct(t_vars *vars);
	void 	run_cd(char **args);
	void 	run_echo (char **args);
	void 	export_cmd(t_vars *vars, char *args);
	void 	check_unset(char **args, t_vars *vars, int check);
	void 	env_cmd(t_vars *vars);
	int 	count_argiment(char **str);

	
#endif