/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haarab <haarab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 13:10:25 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/06 20:04:21 by haarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void run_echo (char **args)
{
    int i = 1;
    int check = 0;

    while (args[i])
    {
        if (ft_strncmp(args[i], "-n", ft_strlen("-n")) == 0)
        {
            check = 1;
            i++;
        }
        printf("%s ", args[i]);
        i++;
    }
    if (check == 0)
        printf("\n");
}

void run_cd(char **args)
{
    if (args[1])
        chdir(args[1]);
}

int count_argiment(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}


int check_argiment(char **args, t_vars *vars, int check)
{
	int count = 0;
	if (args[check])
	{
		int i = 0;
		while (args[check][i])
		{
			if (args[check][i] == '=' && args[check][i + 1] != '\0')
			{
				count++;
			}
			i++;
		}
	}
	int j = 0;
	while (vars->envp[j])
	{
		if (ft_strncmp(vars->envp[j], args[check], ft_strlen(args[check])) == 0)
		{
			return (0);
		}
		j++;
	}
	return (count);
}

void run(char *cmd, char **args, t_vars *vars)
{
    char *cwd = getcwd(NULL, 1024);
	// char *envp;
	// int i;

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
        // if (cwd == NULL)
        // {
        //     printf ("Get current working directory failed.\n");
        //     return ;
        // }
		if (vars->count_argiment > 1)
			printf ("pwd: too many arguments\n");
		else
        	printf ("%s\n", cwd);
    }
	
	else if (ft_strncmp(cmd, "export", ft_strlen("export")) == 0)
	{
		int count = 0;
		while (vars->envp[count])
		{
			printf ("%s\n", vars->envp[count]);
			count++;
		}
		if (vars->count_argiment > 1)
		{
			int i = 1;
			while (args[i])
			{
				if (check_argiment(args, vars, i) >= 1)
				{
					vars->envp[count] = args[i];
					count++;
					printf ("%s\n", args[i]);
				}
				i++;
			}
			vars->envp[count] = 0;
		}
	}
	
	else if (ft_strncmp(cmd, "env", ft_strlen("env")) == 0)
	{
		int count = 0;
		while (vars->envp[count])
		{
			printf ("%s\n", vars->envp[count]);
			count++;
		}
		
	}
	
	else if (ft_strncmp(cmd, "unset", ft_strlen("unset")) == 0)
	{
		int i = 1;
		int j;
		while (args[i])
		{
			j = 0;
			while (vars->envp[j])
			{
				if (ft_strncmp(vars->envp[j], args[i], ft_strlen(args[i])) == 0)
				{
					while (vars->envp[j])
					{
						vars->envp[j] = vars->envp[j + 1];
						j++;
					}
					vars->envp[j] = 0;
				}
				j++;
			}
			i++;
		}
		j = 0;
		while (vars->envp[j])
		{
			printf ("%s\n", vars->envp[j]);
			j++;
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
	// int count = 0;
	t_vars vars;
	(void)v;
	(void)c;
	vars.envp = env;
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