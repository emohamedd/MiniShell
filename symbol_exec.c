/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:13:31 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/18 15:54:49 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define MAX_REDIR 10



// void rot13(char *str) 
// {
//     for (int i = 0; str[i]; i++) 
//     {
//         if ((str[i] >= 'A' && str[i] <= 'Z')) 
//         {
//             str[i] = 'A' + ((str[i] - 'A' + 13) % 26);
//         } 
//         else if ((str[i] >= 'a' && str[i] <= 'z')) 
//         {
//             str[i] = 'a' + ((str[i] - 'a' + 13) % 26);
//         }
//     }
// }

int create_temp_file(char *base_filename) 
{
    // char *file =  malloc(sizeof(char) * (ft_strlen(base_filename) + 1));


    // strcpy(file, base_filename);
    // rot13(file);
    int fd = open(base_filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
    if (fd == -1) 
    {
        perror("open");
        exit(1);
    }
    return fd;
}

void collect_and_write_heredoc(int fd, char *heredoc_delimiter) {
    char *read = NULL;
    char *line;

    while (1) 
    {
        read = readline("> ");
        // read = get_next_line(0);
        ft_putstr_fd(read, fd);
        ft_putstr_fd("\n", fd);
        // printf(" this is the read function : %s\n", read);
        // if (!read) 
        // {
        //     perror("get_next_line");
        //     exit(1);
        // }
        if (strcmp(read, heredoc_delimiter) == 0) 
        {
             printf("U got the delimiter\n");
             dup2(0, fd);
             break;
        }

    }
    close(fd);
}

void pipe_red(t_vars *vars) {
    int i = 0;
    char *base_filename = "emohamed"; 

    while (i < vars->n_commandes) 
    {
        int j = 0;
        int fd = 0;
        if (vars->cmds[i].is_nex_pip) 
        {
            pipe_commands(vars, i);
        }
        if (vars->cmds[i].has_redirections) 
        {
            while (vars->cmds[i].opera_derec[j])
            {
                if (!strcmp(vars->cmds[i].opera_derec[j], ">")) 
                {
                    fd = open(vars->cmds[i].file_derec[j], O_CREAT | O_TRUNC | O_RDWR, 0644);
                    dup2(fd, 1);
                    close(fd);
                } 
                else if (!strcmp(vars->cmds[i].opera_derec[j], "<")) 
                {
                    fd = open(vars->cmds[i].file_derec[j], O_RDWR);
                    dup2(fd, 0);
                    close(fd);
                } 
                else if (!strcmp(vars->cmds[i].opera_derec[j], ">>")) 
                {
                    fd = open(vars->cmds[i].file_derec[j], O_CREAT | O_APPEND | O_RDWR, 0644);
                    dup2(fd, 1);
                    close(fd);
                } 
                else if (!strcmp(vars->cmds[i].opera_derec[j], "<<")) 
                {
                    if (vars->cmds[i].file_derec[j]) 
                    {
                        char *heredoc_delimiter = vars->cmds[i].file_derec[j];
                        printf("the delim : %s\n", heredoc_delimiter);
                        fd = create_temp_file(base_filename);
						
                        collect_and_write_heredoc(fd,  heredoc_delimiter);
                        // fd = create_temp_file(base_filename);
                        close(fd);
                    }
                }
                j++;
            }
        }
        if (!vars->cmds[i].is_nex_pip) {
            exec_cmds(vars, i);
        }
        i++;
    }
}