/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 15:31:58 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/08 20:54:28 by emohamed         ###   ########.fr       */
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
#include <string.h>


#define RED     "\x1B[31m"
#define GREEN   "\x1B[32m"
#define YELLOW  "\x1B[33m"
#define RESET   "\x1B[0m"
#define PURPLE  "\x1B[35m"

// enum golbal_token
// {
//     WORD,
//     PIPE ='|',
//     ENV_VAR = '$',
//     space = ' ',
//     DOUBLE_QUOTE = '\"',
//     SINGLE_QUOTE ='\'',
//     R_OUT = '>',
//     R_IN = '<',
//     DR,
//     HERE_DOC,
// }


typedef struct s_info
{
    char *content;
    char *type;
    int lenght;
    
} t_info;

// enum state{
//     IN_SQ,
//     IN_DQ,
//     GENR
// }

  char *read_input();
  // t_info **ft_split(char *s);
  char **make_token(char *s) ;
  int	count_s_lenght(const char *s, char c);
  char	**ft_split_token(char *s, char c);
  t_info **allocat_token(char **s);
    // size_t	ft_strlen(const char *s);
    // size_t	ft_strlcat(char *dst, char *src, size_t dstsize);
    // int		ft_atoi(const char *str);
    // void	*ft_calloc(size_t count, size_t size);
    // char	*ft_strdup(const char *s1);
    // char	*ft_substr(char const *s, unsigned int start, size_t len);
    // char	*ft_strjoin(char const *s1, char const *s2);
    // char	*ft_itoa(int n);


#endif