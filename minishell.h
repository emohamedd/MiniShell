/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haarab <haarab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 15:31:58 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/23 05:07:51 by haarab           ###   ########.fr       */
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
#include "get_next_line.h"
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <fcntl.h>
#include <signal.h>
#define GRN  "\x1B[32m"
#define BLU  "\x1B[34m"
#define RED  "\x1B[31m"
#define RESET "\x1B[0m"
#define RED     "\x1B[31m"
#define GREEN   "\x1B[32m"
#define YELLOW  "\x1B[33m"
#define RESET   "\x1B[0m"
#define PURPLE  "\x1B[35m"

int her_hand;

typedef struct s_info
{
    char *content;
    char *type;
    int lenght;
    int size;
    
} t_info;

typedef struct s_cmds
{
	char *cmd;
	char **cmds_args;
	char *smbol;
	char **opera_derec;
	char **file_derec;
	int	is_nex_pip;
	int has_redirections;
} t_cmds;

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
	t_cmds *cmds;
    t_env *env;
	int	n_commandes;
	int here_fd;
	
}	t_vars;


	void cmd_exit(char **str, t_vars *vars);
	void	has_redirections(t_vars *vars, int i);
	int		ft_strcmp(char *s1, char *s2);
    char 	**clear_cmds_arg_from_direct(char **args);
    char 	*read_input();
    char 	**get_files(int size, char **old_stac);
    char 	**make_token(char *s) ;
    int 	lenght_of_the_2d(char **p);
    int		count_s_lenght(const char *s, char c);
    t_info 	**allocat_token(char **s, t_vars *cvars);
    char	*ft_strdup(const char *s1);
	char	*ft_getenv(char *key, t_vars *vars);
	void	exec_cmds(t_vars *vars, int i);
    char	*read_input();
    char	**ft_split(char const *s, char c);
	void 	run(char *cmd, char **args, t_vars *vars, char **str);
	void 	fell_env_struct(t_vars *vars);
	void	run_cd(char **args, t_vars *vars);
	void 	run_echo (char **args, t_vars *vars);
	void 	export_cmd(t_vars *vars, char *args, char **str);
	void 	check_unset(char **args, t_vars *vars, int check);
	void 	env_cmd(t_vars *vars);
    void 	table(char **str, t_info **tokens);
	int 	count_argiment(char **str);
    void 	syn_err(char **str, t_vars *vars);
    void 	fill_commands(char **ptr, t_vars *vars);
	void 	pipe_commands(t_vars *vars, int i, pid_t *childs);
	char 	**red_to_herdoc(char **tokens);
	char 	*get_path(t_vars *vars, char *cmd);
	int 	is_redirection(char *arg);
    char	*ft_getenv(char *key, t_vars *vars);
	char	**get_redirectinsv(int size, char **old_stack);
    char	**get_cmds(t_info **info);
    void	sigintHandler(int signal);
    void	fell_env_struct(t_vars *vars);
    void	fell_env_struct(t_vars *vars);
    char	*ft_getenv(char *key, t_vars *vars);
    void	pipe_red(t_vars *vars, int i, pid_t *childs);
	void	sigintHandler2();
	char**  expand_s_quotes(char** tokens);

#endif