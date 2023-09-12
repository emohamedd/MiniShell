/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haarab <haarab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 15:31:58 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/11 21:06:21 by haarab           ###   ########.fr       */
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
#include "libft/libft.h"
#include "get_next_line/get_next_line.h"
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

#define GRN  "\x1B[32m"
#define BLU  "\x1B[34m"
#define RED  "\x1B[31m"
#define RESET "\x1B[0m"

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
    int size;
    
} t_info;

// enum state{
//     IN_SQ,
//     IN_DQ,
//     GENR
// }

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
	int exit_status;
    t_env *env;
}	t_vars;

  char *read_input();
  // t_info **ft_split(char *s);
  char **make_token(char *s) ;
  int lenght_of_the_2d(char **p);
  int	count_s_lenght(const char *s, char c);
//   char	**ft_split_token(char *s, char c);
  t_info **allocat_token(char **s, t_vars *cvars);
  char	*ft_strdup(const char *s1);
//   size_t	ft_strlen(const char *s);
	char	*ft_getenv(char *key, t_vars *vars);
	void	exec_cmds(t_vars *vars, char *cmd, char **args);
    void	display_prompt();
    char	*read_input();
    char	**ft_split(char const *s, char c);
	void 	run(char *cmd, char **args, t_vars *vars);
	void 	fell_env_struct(t_vars *vars);
	void	run_cd(char **args, t_vars *vars);
	void 	run_echo (char **args, t_vars *vars);
	void 	export_cmd(t_vars *vars, char *args, char **str);
	void 	check_unset(char **args, t_vars *vars, int check);
	void 	env_cmd(t_vars *vars);
    void 	table(char **str, t_info **tokens);
	int 	count_argiment(char **str);
    // t_info **ft_splite(char *s) ;
    // size_t	ft_strlen(const char *s);
    // size_t	ft_strlcat(char *dst, char *src, size_t dstsize);
    // int		ft_atoi(const char *str);
    // void	*ft_calloc(size_t count, size_t size);
    // char	*ft_strdup(const char *s1);
    // char	*ft_substr(char const *s, unsigned int start, size_t len);
    // char	*ft_strjoin(char const *s1, char const *s2);
    // char	*ft_itoa(int n);



	
#endif
