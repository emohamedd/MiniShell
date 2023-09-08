/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haarab <haarab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:52:40 by haarab            #+#    #+#             */
/*   Updated: 2023/09/08 21:58:52 by haarab           ###   ########.fr       */
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

int check_bin(char **path, int count)
{
	int i = 0;
	char *bin = "bin";
	while (i < count)
	{
		int j = 0;
		while (path[i][j])
		{
			j++;
		}
		j = j - 3;
		int k = 0;
		while (path[i][j])
		{
			if (path[i][j] == bin[k])
			{
				k++;
			}
			if (k == 3)
			{
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
int check_state(char *folder, t_vars __unused *var, char *cmd)
{
	struct stat s;
	struct dirent	*dir_info = NULL;
	DIR				*dir_str;
	
	if (stat(folder, &s) && s.st_mode & S_IFDIR)
	{
		dir_str = opendir(folder);
		if (!dir_info)
			return (0);
		dir_info = readdir(dir_str);
		while (dir_info )
		{
			if (ft_strncmp(dir_info->d_name, cmd, ft_strlen(cmd)))
			{
				closedir(dir_str);
				return (1);
			}
			dir_info++;
			dir_info = readdir(dir_str);
		}
		closedir(dir_str);
	}
	return (0);
}
char *check_path(t_vars __unused *var, char **path, char *cmd)
{
	int i = 0;
	while (path[i])
	{
		if (check_state(path[i], var, cmd))
			return (ft_strjoin("/bin/", cmd));
		i++;
	}
	return (NULL);
}

char *get_path(t_vars *vars, char *cmd)
{
	int i = 0;
	char **path;
	char *res = NULL;
	while (i < vars->env_number)
	{
		if (ft_strncmp(vars->env[i].key, "PATH", ft_strlen("PATH")) == 0)
		{
			int count = count_strings(vars->env[i].value, ':');
			// printf ("%d\n", count);
			path = ft_split(vars->env[i].value, ':');
			if (check_bin(path, count))
			{
				printf ("hna\n");
				char *str = check_path(vars, path, cmd);
				printf ("%s\n" , str);
				
				return (check_path(vars, path, cmd));
			
			}
			// else 
				// res = NULL;
			// printf ("%d\n", check);
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
        run_cd(args);
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
	
    else
    {
		char *str;
		str = get_path(vars, cmd);

		// printf ("%s\n", str);
        // int pid = fork();
        // if (pid == 0)
        // {
		// 	// if (str == NULL)
		// 	// 	perrer("command not found");
		// 	// // cmd = ft_strjoin("/bin/", cmd);
        //     // if (execve(cmd, args, vars->envp) == -1)
		// 	// 	perror ("execve: ERROR");
        //     execve(cmd, args, vars->envp);
		// 		// perror ("execve: ERROR");
        // }
        // else
        //     wait(NULL);
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
		if (str[0] != NULL)
		{
			char* command = str[0];
			char **args = str;
			vars.count_argiment = count_argiment(args);
			run(command, args, &vars);
		}
    }
    return 0;
}