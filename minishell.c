/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haarab <haarab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 13:10:25 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/07 15:29:40 by haarab           ###   ########.fr       */
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


// int check_argiment(char **args, t_vars *vars, int check)
// {
// 	int count = 0;
// 	if (args[check])
// 	{
// 		int i = 0;
// 		while (args[check][i])
// 		{
// 			if (args[check][i] == '=' && args[check][i + 1] != '\0')
// 			{
// 				count++;
// 			}
// 			i++;
// 		}
// 	}
// 	int j = 0;
// 	while (vars->envp[j])
// 	{
// 		if (ft_strncmp(vars->envp[j], args[check], ft_strlen(args[check])) == 0)
// 		{
// 			return (0);
// 		}
// 		j++;
// 	}
// 	return (count);
// }

// void fell_string(t_vars *vars, char **args, int check)
// {
// 	char *key = ft_split(args[check], '=')[0];
// 	vars->strarg = key;
// 	if (ft_strchr(args[check], '='))
// 	{
// 		vars->strvalue = ft_strchr(args[check], '=') + 1;
// 	}
// }

void check_unset(char **args, t_vars *vars, int check)
{
	int i = 0;
	char *key;

	key = args[check];
	while (i < count_argiment(vars->envp))
	{
		// printf ("%s\n", vars->env[i].key);
		// printf("ana hna\n");
		int ma = ft_strncmp(vars->env[i].key, key, ft_strlen(key));
		if (ma == 0)
		{
			while (i < count_argiment(vars->envp))
			{
				vars->envp[i] = vars->envp[i + 1];
				i++;
			}
			vars->envp[i] = 0;
		}
		// {
		// 	i = 0;
		// 	// return (1);
		// }
		i++;
	}
}

int check_argiment(char **args, t_vars *vars, int check)
{
	int i = 0;
	char *key;
	char *value;

	key = ft_split(args[check], '=')[0];
	printf ("%s\n", key);
	value =ft_strchr(args[check], '=') + 1;
	printf ("%s\n", value);
	while (i < count_argiment(vars->envp))
	{
		printf ("%s\n", vars->env[i].key);
		if (ft_strncmp(key, vars->env[i].key, ft_strlen(vars->env[i].key) == 0)
			&& ft_strncmp(value, vars->env[i].value, ft_strlen(vars->env[i].value) != 0))
		{
			// vars->env[i].value = value;
			return (1);
		}
		i++;
	}
	return (0);
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

void env_cmd(t_vars *vars)
{
    int i = 0;
    while (i < count_argiment(vars->envp))
	{
        if (vars->env[i].is_equal)
		{
            printf("%s", vars->env[i].key);
            printf("=");
            printf("%s\n", vars->env[i].value);
        }
        i++;
    }
}

void export_cmd(t_vars *vars, char **args)
{
    int count = 0;
	
	while (count < count_argiment(vars->envp))
	{
        count++;
	}
	if (vars->count_argiment > 1)
    {
        int i = 1;
        while (args[i])
        {
			// if (check_argiment(args, vars, i) == 0)
			// {
				
			// }
            if (ft_strchr(args[i], '=') != NULL)
            {
                vars->envp[count] = args[i];
                count++;
            }
            i++;
        }
        vars->envp[count] = 0;
    }
	count = 0;
	if (vars->count_argiment == 1)
	{
		while (count < count_argiment(vars->envp))
		{
			if (vars->env[count].is_equal)
			{
				printf("%s", vars->env[count].key);
				printf("=");
				printf("%s\n", vars->env[count].value);
			}
			count++;
		}
	}
}

// void export_cmd(t_vars *vars, char **args)
// {
//     int count = 0;
// 	while (vars->envp[count])
//     {
//         printf ("%s\n", vars->envp[count]);
//         count++;
//     }
//     if (vars->count_argiment > 1)
//     {
//         int i = 1;
//         while (args[i])
//         {
//             if (ft_strchr(args[i], '=') != NULL)
//             {
//                 vars->envp[count] = args[i];
//                 count++;
//                 printf ("%s\n", args[i]);
//             }
//             i++;
//         }
//         vars->envp[count] = 0;
//     }
// }


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
		if (vars->count_argiment > 1)
			printf ("pwd: too many arguments\n");
		else
        	printf ("%s\n", cwd);
    }
	
	else if (ft_strncmp(cmd, "export", ft_strlen("export")) == 0)
	{
		export_cmd(vars, args);
	}
	
	else if (ft_strncmp(cmd, "env", ft_strlen("env")) == 0)
	{
		env_cmd(vars);
	}
	else if (ft_strncmp(cmd, "unset", ft_strlen("unset")) == 0)
	{
		int i = 1;
		// int j;
		while (args[i])
		{
			check_unset(args, vars, i);
		// 	j = 0;
		// 	while (vars->envp[j])
		// 	{
		// 		if (ft_strncmp(vars->envp[j], args[i], ft_strlen(args[i])) == 0)
		// 		{
		// 			while (vars->envp[j])
		// 			{
		// 				vars->envp[j] = vars->envp[j + 1];
		// 				j++;
		// 			}
		// 			vars->envp[j] = 0;
		// 		}
		// 		j++;
		// 	}
			i++;
		}
		// j = 0;
		// while (vars->envp[j])
		// {
		// 	printf ("%s\n", vars->envp[j]);
		// 	j++;
		// }
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
    vars.env = malloc(sizeof(t_env) * (count_argiment(vars.envp)));
    while(1)
    {
    	fell_env_struct(&vars);
        input = read_input();
        str = ft_split(input, ' ');
        char* command = str[0];
        char **args = str;
		vars.count_argiment = count_argiment(args);
        run(command, args, &vars);
    }
    return 0;
}