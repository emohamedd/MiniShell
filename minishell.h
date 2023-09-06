/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haarab <haarab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 15:31:58 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/06 17:26:46 by haarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

// int system(const char* command);


#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include "libft/libft.h"
#include <sys/wait.h>

typedef struct s_vars
{
	int	count_argiment;
	char **envp;
}	t_vars;

typedef struct s_var
{
	int	count_string;
	char *first_string;
	char *key;
	char *last_string;
}	t_var;

    void display_prompt();
    char *read_input();
    char	**ft_split(char const *s, char c);
    char **split_input(char *str);
    int	count_s_lenght(const char *s, char c);
    // size_t	ft_strlen(const char *s);
    // size_t	ft_strlcat(char *dst, char *src, size_t dstsize);
    // int		ft_atoi(const char *str);
    // void	*ft_calloc(size_t count, size_t size);
    // char	*ft_strdup(const char *s1);
    // char	*ft_substr(char const *s, unsigned int start, size_t len);
    // char	*ft_strjoin(char const *s1, char const *s2);
    // char	*ft_itoa(int n);

#endif