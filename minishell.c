/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haarab <haarab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 13:10:25 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/13 20:06:13 by haarab           ###   ########.fr       */
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
	char *fullCmd;
	path = ft_split(res, ':');
	struct stat file_info;
	while (path[i]) {
		fullCmd = ft_strjoin(ft_strjoin(path[i], "/"), cmd);
		if (stat(fullCmd, &file_info) == 0) {
			return fullCmd;
		}
		i++;
	}
	return (NULL);
}

void run(char *cmd, char **args, t_vars *vars, char *str)
{
	char *cwd = getcwd(NULL, 1024);

    if (ft_strncmp(cmd, "echo", ft_strlen("echo")) == 0)
    {
		// int kl = 2;
        run_echo(args, vars);
		// kl = ft_strncmp(("$?"), args[1], ft_strlen(args[1]) == 0);
		// printf("%d\n", kl);
		// if (kl == 0)
		// {
		// 	printf("%d\n", vars->exit_status);
		// }
		// printf ("%s\n", args[1]);
		// if (ft_strncmp(args[1], "$?", ft_strlen("$?")) == 0)
			// printf ("exit status %d\n", vars->exit_status);
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
			export_cmd(vars, NULL, NULL);
		int i = 1;
		while (args[i])
		{
			export_cmd(vars, args[i], args);
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
	char *path;
	path = get_path(vars, cmd);

	id = fork();
	if (id == 0) 
	{
		if (path == NULL)
		{
			ft_putstr_fd("minishell : ", 2);
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": command not found\n", 2);
			exit(127);
			
		}
		else if (execve(path, args, vars->envp) == -1)
		{
			perror("execve");
			exit(126);
		}
	}
	wait(&vars->exit_status);
	vars->exit_status = WEXITSTATUS(vars->exit_status);
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


void pipe_commands(t_vars *vars, int d) 
{
	int status;
	char *path;
    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) 
    {
        perror("pipe");
        exit(1);
    }
	int i = 0;
	d = d - 1;
	while (i < d)
	{
   		pid_t child1;
    	child1 = fork();
		if (child1 == -1) 
    	{
        	perror("fork");
        	exit(1);
    	}
		if (child1 == 0) 
		{
			close(pipe_fd[0]);
			// dup2(pipe_fd[1], STDOUT_FILENO);
			if (dup2(pipe_fd[1], STDOUT_FILENO) == -1) 
        	{
            	perror("dup2");
            	exit(1);
        	}
			close(pipe_fd[1]);
			path = get_path(vars, vars->cmds[i].cmd);
			execve(path, vars->cmds[i].cmds_args, vars->envp);
			exit(0);
		} 
		else 
		{
			close(pipe_fd[1]);
			// dup2(pipe_fd[0], STDIN_FILENO);
			if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
			{
                perror("dup2");
                exit(1);
			}
			close(pipe_fd[0]);
			path = get_path(vars, vars->cmds[i + 1].cmd);
			int id  = fork();
			if (id == -1) 
			{
            	perror("fork");
            	exit(1);
        	}
			if (id  == 0)	
				execve(path, vars->cmds[i + 1].cmds_args, vars->envp);
			else
				waitpid(id, &status, 0);
			waitpid(child1, &status, 0);
		}
		i++;
	}
}



void pipeline(char *str, t_vars *vars)
{
	int i = 0;
	int j = 0;
	int l = 0;
	char **ptr;
	
	ptr = ft_split(str, ' ');
	if (!ptr)
		return;
	while (ptr[i])
	{
		if (ft_strncmp(ptr[i], "|", ft_strlen("|")) != 0)
		{
			if (ft_strncmp("|", ptr[i + 1], ft_strlen(ptr[i + 1])) == 0)
				l++;
		}
		if (ft_strncmp(ptr[i], "|", ft_strlen("|")) == 0)
			l++;
		i++;
	}

	vars->cmds = malloc(sizeof(t_cmds) * (l));
	char **split_pip = ft_split(str, '|');
	i = 0;
	int k = 0;
	while (split_pip[i])
	{
		j = 0;
		char **split_cmd = ft_split(split_pip[i], ' ');
		while (split_cmd[j])
		{
			vars->cmds[i].cmd = split_cmd[0];
			vars->cmds[i].cmds_args = split_cmd;
			j++;
		}
		i++;
	}
	// printf ("%d\n", vars->cmds->size);
	pipe_commands(vars, i);

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
    while(1)
    {
        input = read_input();
        if (input == NULL)
            return (vars.exit_status);
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
			vars.count_argiment = lenght_of_the_2d(str);
			int fdin = dup(STDIN_FILENO);
			int fdou = dup(STDOUT_FILENO);
			if (ft_strchr(input, '|') == NULL)
				run(tokens[0]->content, cmds, &vars, input);
			else 
				pipeline(input, &vars);
			dup2(fdin, 0);
			dup2(fdou, 1);
			// run(tokens[0]->content, cmds, &vars);
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

//lez beda bda kayban hadchi db baybqaw dok les cas dyal quote wst mnha expand dak tkhrbiq kaymrd mohim beda bdat katban qadia
//yalah a hamza byn lia tanta ach endk
// good luck mate :)
