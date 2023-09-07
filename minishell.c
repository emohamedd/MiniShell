/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haarab <haarab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:52:40 by haarab            #+#    #+#             */
/*   Updated: 2023/09/07 19:52:41 by haarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void run_cd(char **args)
{
    if (args[1])
        chdir(args[1]);
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

void run(char *cmd, char **args, t_vars *vars)
{
    char *cwd = getcwd(NULL, 1024);

    if (ft_strncmp(cmd, "echo", ft_strlen("echo")) == 0)
    {
        run_echo(args);
    }
	
    else if (ft_strncmp(cmd, "cd", ft_strlen("cd")) == 0)
    {
        run_cd(args);
    }
	
    else if (ft_strncmp(cmd, "ls", ft_strlen("ls")) == 0)
    {
        int pid = fork();
        if (pid == 0)
        {
            execve("/bin/ls", args, NULL);
        }
        else
        {
            wait(NULL);
        }
    }
	
    else if (ft_strncmp(cmd, "pwd", ft_strlen("pwd")) == 0)
    {
		if (vars->count_argiment > 1)
			printf ("pwd: too many arguments\n");
		else
        	printf ("%s\n", cwd);
    }
	
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
    {
        exit (1);
    }
}


int main(int c, char **v, char **env)
{
    char *input;
    char **str;
	t_vars vars;
	(void)v;
	(void)c;
	vars.envp = env;
    vars.env = malloc(sizeof(t_env) * (count_argiment(vars.envp)));
    fell_env_struct(&vars);
	vars.env_number = count_argiment(vars.envp);
    while(1)
    {
        input = read_input();
        str = ft_split(input, ' ');
        char* command = str[0];
        char **args = str;
		vars.count_argiment = count_argiment(args);
        run(command, args, &vars);
    }
    return 0;
}