/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 15:31:58 by emohamed          #+#    #+#             */
/*   Updated: 2023/10/01 00:01:51 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <string.h>
# include "libft/libft.h"
# include "malloc/ft_malloc.h"
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <dirent.h>
# include <fcntl.h>
# include <signal.h>
# define GRN  "\x1B[32m"
# define BLU  "\x1B[34m"
# define RED  "\x1B[31m"
# define RESET "\x1B[0m"
# define RED     "\x1B[31m"
# define GREEN   "\x1B[32m"
# define YELLOW  "\x1B[33m"
# define RESET   "\x1B[0m"
# define PURPLE  "\x1B[35m"

int			g_exit_status;
typedef struct s_info
{
	char	*content;
	char	*type;
	int		lenght;
	int		size;

}			t_info;

typedef struct s_cmds
{
	char	*cmd;
	char	**cmds_args;
	char	*smbol;
	char	**opera_derec;
	char	**file_derec;
	int		is_nex_pip;
	int		has_redirections;
}			t_cmds;

typedef struct s_env
{
	char	*key;
	int		is_equal;
	char	*value;
}			t_env;

typedef struct s_int
{
	int		b;
	int		k;
	int		size_of_direc;
}			t_int;

typedef struct s_dq
{
	int		num_quotes;
	int		total_tokens;
	int		i;
	char	**expanded_tokens;
	int		j;
	char	*current_token;
	char	*modified_token;
}			t_dq;

typedef struct s_sq
{
	int		num_quotes;
	int		total_tokens;
	int		i;
	char	**expanded_tokens;
	int		j;
	char	*current_token;
}			t_sq;

typedef struct s_ev
{
	int		i;
	char	*key;
	char	*dst1;
	char	*dst2;
	char	*dst3;
	char	*exp_value;
}			t_ev;

typedef struct s_sp
{
	int		max_tokens;
	char	**tokens;
	int		token_count;
	char	*start;
	char	*end;
	int		in_quotes;
	char	quote_char;
	int		escaped;
	int		i;
	char	**new_tokens;
}			t_sp;

typedef struct s_cp
{
	int		i;
	int		j;
}			t_cp;

typedef struct s_run
{
	char	**str;
	char	*input;
	char	*trimed;
	char	**cmds;
	int		fdin;
	int		fdou;
}			t_run;

typedef struct s_export
{
	int		d;
	int		x;
	int		p;
	int		count;
}			t_export;

typedef struct s_fill
{
	int		i;
	int		b;
}			t_fill;

typedef struct s_vars
{
	int		count_argiment;
	int		env_number;
	char	**envp;
	char	*strarg;
	char	*strvalue;
	t_cmds	*cmds;
	t_env	*env;
	int		n_commandes;
	int		here_fd;
	int		i;
}			t_vars;

typedef struct s_data
{
	int		fd[2];
	int		prev_fd;
	char	*path;
}	t_data;

int			handle_input_redirection(char *filename);
int			handle_output_redirection(char *filename);
int			handle_append_redirection(char *filename);
t_sp		realloc_tokens(t_sp sp);
t_sp		handle_token(t_sp sp);
int			handle_heredoc(char *filename);
t_sp		handle_last_token(t_sp sp);

void		run_export(t_vars *vars, int i);
void		run_unset(t_vars *vars, int i);
void		run_exit(t_vars *vars, int i);
void		run_pwd(char *cwd);
void		free_x_max(char **str);
void		cmd_exit(char **str);
int			has_redirections(t_vars *vars, int i);
int			ft_strcmp(char *s1, char *s2);
char		**clear_cmds_arg_from_direct(char **args);
char		*read_input(void);
char		**get_files(int size, char **old_stac);
char		**make_token(char *s);
int			lenght_of_the_2d(char **p);
int			count_s_lenght(const char *s, char c);
t_info		**allocat_token(char **s, t_vars *cvars);
char		*ft_strdup(const char *s1);
char		*ft_getenv(char *key, t_vars *vars);
void		exec_cmds(t_vars *vars, int i);
char		*read_input(void);
char		**ft_split(char const *s, char c);
void		run(char **args, t_vars *vars);
void		fell_env_struct(t_vars *vars);
void		run_cd(char **args, t_vars *vars, char *pwd);
void		run_echo(char **args);
void		export_cmd(t_vars *vars, char *args);
void		check_unset(char **args, t_vars *vars, int check);
void		env_cmd(t_vars *vars);
void		table(char **str, t_info **tokens);
int			count_argiment(char **str);
void		syn_err(char **str, t_vars *vars);
void		fill_commands(char **ptr, t_vars *vars);
void		pipe_commands(t_vars *vars, int i, pid_t *childs);
char		**red_to_herdoc(char **tokens);
char		*get_path(t_vars *vars, char *cmd);
int			is_redirection(char *arg);
char		*ft_getenv(char *key, t_vars *vars);
char		**get_redirectinsv(int size, char **old_stack);
char		**get_cmds(t_info **info);
void		siginthandler(int signal);
void		fell_env_struct(t_vars *vars);
void		fell_env_struct(t_vars *vars);
char		*ft_getenv(char *key, t_vars *vars);
void		pipe_red(t_vars *vars, int i, pid_t *childs);
void		cmd_builtins(t_vars *vars, int i);
int			syntax_errors(char **args);
void		is_notbuiltins(t_vars *vars, int i, pid_t *childs);
void		ft_builtins(t_vars *vars, int i, pid_t *childs);
int			command_notfound(char **args, t_vars *vars);
int			syntax_err(char **args);
void		change_pwd(t_vars *vars, char *pwd);
char		**expand_s_quotes(char **tokens);
char		**expand_quotes(char **tokens);
void		change_oldpwd(t_vars *vars, char *pwd);
char		**ft_split_export(char const *s, char c);
char		*allocat_s_export(const char *s, char c);
int			count_s_lenght_export(const char *s, char c);
void		free_x_dmax(char **str);
int			double_quotes(char **args);
char		*dp_en(const char *s1);
char		*ft_strdup_against(const char *s1);
char		*ft_strjoin_export(char const *s1, char const *s2);
char		*ft_strdup_export(const char *s1);
void		*ft_calloc_export(size_t count, size_t size);
char		**ft_split_export(char const *s, char c);
char		**split(char *s, char *delimiters);
char		*ft_strndup(char const *str, size_t max);
char		*expand_var(char *arg, t_vars *vars);
int			is_var_inside_sq(char *arg, int index);
int			gvs(char *str);
char		*ft_strcpy(char *destination, const char *source);
char		*ft_strcat(char *destination, const char *source);
char		*ft_strncpy(char *destination, char *source, int n);
void		fell_env(t_vars *vars, char *args, char *key, t_export *export_int);
int			check_key(char *args);
int			fell_env_value(t_vars *vars, char *args, int count, char *var_);
void		print_env(t_vars *vars, int count);
int			redirect_output(t_vars *vars, int j, int i);
int			redirect_input(t_vars *vars, int j, int i);
int			redirect_output_append(t_vars *vars, int j, int i);

#endif