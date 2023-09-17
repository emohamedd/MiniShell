/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 13:10:25 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/17 19:00:43 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void fell_env_struct(t_vars *vars)
{
    int i = 0;
    char *key;
    while (vars->envp[i])
	{
        key = ft_split(vars->envp[i], '=')[0];
        vars->env[i].key = key;
        if (ft_strchr(vars->envp[i], '='))
		{
            vars->env[i].is_equal = 1;
            vars->env[i].value = ft_strchr(vars->envp[i], '=') + 1;
        }
        i++;
    }
}

char *ft_getenv(char *key, t_vars *vars)
{
	int i;

	i = 0;
	while (i < vars->env_number) {
		if (!ft_strncmp(vars->env[i].key, key, ft_strlen(key))) {
			return (vars->env[i].value);
		}
		i++;
	}
	return NULL;
}



void	setup_redirs(char **args, t_vars *vars)
{
	int i =0;

	while (args[i] && strcmp(args[i], "|"))
	{
		// printf("***%s***\n", args[i]);
		if(!strcmp(args[i], ">"))
		{
			++i;
			int fd = open(args[i], O_CREAT | O_TRUNC | O_RDWR, 0644);
			dup2(fd, 1);
		}
		if (!strcmp(args[i], "<"))
		{
			++i;
			int fd = open(args[i], O_RDONLY , 0644);
			dup2(fd, 0);
		}
		i++;
	}	
}


char	**get_cmds(t_info **info)
{
	int		len = 0;
	int		i;
	char	*cmd = NULL;

	len = (*info)->size;
	i = 0;
	while (i < len)
	{
		cmd = ft_strjoin(cmd, info[i]->content);
		cmd = ft_strjoin(cmd, " ");
		i++;
	}
	return (ft_split(cmd, ' '));
}

char *swap(char **str)
{
    int  i = 0;
    char *s = NULL;
    while(str[i])
    {

      s = ft_strjoin(s, str[i]);
      i++;
      if (str[i])
        s = ft_strjoin(s, " ");
    }
    return s;
}

int lenght_of_2d_splited(char **p)
{
    int i = 0;
    while((ft_strncmp(p[i], "|", ft_strlen("|")) != 0))
    {
        i++;
    }
    return i;
}


void  fill_commands(char **ptr, t_vars *vars)
{
	int i = 0;
	int j = 0;
	int l = 1;
	
	while (ptr[i])
	{
		if (ptr[i + 1] && (ft_strncmp("|", ptr[i + 1], ft_strlen(ptr[i + 1])) == 0))
			l++;
		// printf("---%s\n", ptr[i]);
		// printf()
		i++;
	}
	
	vars->cmds = malloc(sizeof(t_cmds) * (l + 1));
	i = 0;
	int h = 0;
	int b = 0;
	while (i < l)
	{
		while (ptr[b] && (ft_strncmp("|", ptr[b], ft_strlen(ptr[b]))))
				b++;
		if (!ft_strncmp("|", ptr[b], ft_strlen(ptr[b])))
			b++;
		vars->cmds[i].cmds_args = malloc(sizeof(char *) * (b + 1));
		i++;
	}
	
	i = 0;
	b = 0;
	int k = 0;
	int size_of_direc = 0;
	while (i < l)
	{
		size_of_direc = 0;
		k = 0;
		vars->cmds[i].cmd = ptr[b];
		while (ptr[b] && ft_strncmp("|", ptr[b], ft_strlen(ptr[b])))
		{
			if (is_redirection(ptr[b]))
				size_of_direc++;
			vars->cmds[i].cmds_args[k] = ptr[b];
			b++;
			k++;
		}
		vars->cmds[i].cmds_args[k] = 0;
		if (size_of_direc > 0)
		{
			vars->cmds[i].opera_derec = get_redirectinsv(size_of_direc, vars->cmds[i].cmds_args);
			vars->cmds[i].file_derec = get_files(size_of_direc, vars->cmds[i].cmds_args);
			vars->cmds[i].has_redirections = 1;
			vars->cmds[i].cmds_args = clear_cmds_arg_from_direct(vars->cmds[i].cmds_args);
		}
		else
			vars->cmds[i].has_redirections = 0;
		if (ptr[b] && !ft_strncmp("|", ptr[b], ft_strlen(ptr[b])))
		{
			// vars->cmds[i].smbol = ptr[b];
			vars->cmds[i].is_nex_pip = 1;
			k++;
		}
		else
			vars->cmds[i].is_nex_pip = 0;
		b++;
		i++;
	}
	vars->n_commandes = l;
}

void sigintHandler(int signal) 
{
	 if (signal == SIGINT)
    {
        // printf("\n");
        rl_on_new_line();
        // rl_replace_line("", 0);
        rl_redisplay();
    }
}

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
            return (vars.exit_status);
		if (!input[0])
			continue;
		str =  make_token(input);
        // str = ft_split(input, ' ');
		if(str)
        {
			tokens = allocat_token(str, &vars);
			if(!tokens)
				continue;
			cmds = get_cmds(tokens);
			if (!cmds)
				return (0);
			syn_err(cmds, &vars);
			vars.count_argiment = lenght_of_the_2d(str);
			int fdin = dup(STDIN_FILENO);
			int fdou = dup(STDOUT_FILENO);
			// if (ft_strchr(input, '|') == NULL)
			run(tokens[0]->content, cmds, &vars, input);
			// else 
			// 	fill_commands(cmds, &vars);
			dup2(fdin, 0);
			dup2(fdou, 1);
			// table(str, tokens);
        }
		// if (str[0] != NULL)
		// {
		// 	char* command = str[0];
		// 	char **args = str;
		// 	vars.count_argiment = count_argiment(args);
		// 	run(command, args, &vars);
		// }
    }
	
    return 0;
}
