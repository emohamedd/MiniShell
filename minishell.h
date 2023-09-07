/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haarab <haarab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 15:31:58 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/07 13:03:44 by haarab           ###   ########.fr       */
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
	char **envp;
	char *strarg;
	char *strvalue;
    t_env *env;
}	t_vars;

    void display_prompt();
    char *read_input();
    char	**ft_split(char const *s, char c);
    char **split_input(char *str);
    int	count_s_lenght(const char *s, char c);

#endif