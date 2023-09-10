/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haarab <haarab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 13:10:25 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/10 13:30:09 by haarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void run_cd(char **args, t_vars *vars)
{
    if (args[1])
        chdir(args[1]);
	else if (!args[1])
		chdir(ft_getenv("HOME", vars));
}

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

char *get_path(t_vars *vars, char *cmd)
{
	int i = 0;
	char **path;
	char *res;
	
	if (ft_strchr(cmd, '/')) 
		return cmd;
	res = ft_getenv("PATH", vars);
	if(res == NULL)
		return (NULL);
	path = ft_split(res, ':');
	struct stat file_info;
	while (path[i]) {
		char *fullCmd = ft_strjoin(ft_strjoin(path[i], "/"), cmd);
		if (stat(fullCmd, &file_info) == 0) {
			return fullCmd;
		}
		i++;
	}
	return (res);
}

void run(char *cmd, char **args, t_vars *vars)
{
	char *cwd = getcwd(NULL, 1024);

    if (ft_strncmp(cmd, "echo", ft_strlen("echo")) == 0)
    {
        run_echo(args);
    }
	
    else if (ft_strncmp(cmd, "cd", ft_strlen("cd")) == 0)
    {
        run_cd(args, vars);
    }
	
	
    else if (ft_strncmp(cmd, "pwd", ft_strlen("pwd")) == 0)
    {
		printf ("%s\n", cwd);
    }
	
	// export fiha mochkil args[i]->content katjib l3adad ghalt dyal lea argiment
	// export a="b" kat3tabrha 2 argiment hadi khasha thandla
	// 
	
	else if (ft_strncmp(cmd, "export", ft_strlen("export")) == 0)
	{
		if (!args[1])
			export_cmd(vars, NULL);
		int i = 1;
		while (args[i])
		{
			export_cmd(vars, args[i]);
			i++;
		}
	}
	
	else if (ft_strncmp(cmd, "env", ft_strlen("env")) == 0)
	{
		env_cmd(vars);
	}
	else if (ft_strncmp(cmd, "unset", ft_strlen("unset")) == 0)
	{
		int i = 1;
		while (args[i])
		{
			check_unset(args, vars, i);
			i++;
		}
	}

    else if (ft_strncmp(cmd, "exit", ft_strlen("exit")) == 0)
        exit (1);
    else
		exec_cmds(vars, cmd, args);
}



//	kayn mochkil fdak strak dyalk dayr mochkil execve 
//	ls cat ... mra kaykhedmo mera makaykhedmoch

void exec_cmds(t_vars *vars, char *cmd, char **args) {
	int id;

	id = fork();
	if (id == 0) {
		if (execve(get_path(vars, cmd), args, NULL) == -1 ) {
			ft_putstr_fd("minishell : ", 2);
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": command not found\n", 2);
			exit(127);
		}
	}else {
		waitpid(id, NULL, 0);
	}
}

// hadchi fih bzaffff dyal handlaj asat rak ghir msahal hadchi

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


int main(int c, char **v, char **env)
{
	char **str;
	t_vars vars;
	char **cmds;
	
	cmds = NULL;
	v += c;
	vars.envp = env;
    vars.env = malloc(sizeof(t_env) * (count_argiment(vars.envp)));
    fell_env_struct(&vars);
	vars.env_number = count_argiment(vars.envp);
    char *input;
    t_info **tokens = NULL; 
    while(1)
    {
        input = read_input();
        if (input == NULL)
            return (1);
            str =  make_token(input);
        if(str)
        {
        tokens = allocat_token(str, &vars);
        if(!tokens)
            continue;
		cmds = get_cmds(tokens);
		if (!cmds)
			return (0);
		vars.count_argiment = lenght_of_the_2d(str);
		run(tokens[0]->content, cmds, &vars);
		table(str, tokens);
        }
    }
    return 0;
}

//lez beda bda kayban hadchi db baybqaw dok les cas dyal quote wst mnha expand dak tkhrbiq kaymrd mohim beda bdat katban qadia
//yalah a hamza byn lia tanta ach endk
// good luck mate :)
