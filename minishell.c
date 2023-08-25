/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 13:10:25 by emohamed          #+#    #+#             */
/*   Updated: 2023/07/30 19:34:54 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// #include <direct.h>

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

void run(char *cmd, char **args)
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
        if (cwd == NULL)
        {
            printf ("Get current working directory failed.\n");
            return ;
        }
        printf ("%s\n", cwd);
        free (cwd);
    }
    else if (ft_strncmp(cmd, "exit", ft_strlen("exit")) == 0)
    {
        exit (1);
    }
}

int main()
{
    char *input;
    char **str;
    while(1)
    {
        input = read_input();
        str = ft_split(input, ' ');
        char* command = str[0];
        char **args = str;
        run(command, args);
    }
    return 0;
}
