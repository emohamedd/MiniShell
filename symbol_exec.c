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



void rot13(char *str) {
    for (int i = 0; str[i]; i++) {
        if ((str[i] >= 'A' && str[i] <= 'Z')) {
            str[i] = 'A' + ((str[i] - 'A' + 13) % 26);
        } else if ((str[i] >= 'a' && str[i] <= 'z')) {
            str[i] = 'a' + ((str[i] - 'a' + 13) % 26);
        }
    }
}

int create_temp_file(const char *base_filename) {
    char transformed_filename[64];


    strcpy(transformed_filename, base_filename);
    rot13(transformed_filename);

    int fd = open(transformed_filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
    if (fd == -1) {
        perror("open");
        exit(1);
    }
    return fd;
}

void collect_and_write_heredoc(int fd, const char *heredoc_delimiter) {
    char *line = NULL;
    size_t line_size = 0;
    ssize_t bytes_read;

    printf("Heredoc started. Enter lines of text, or type '%s' on a line by itself to end.\n", heredoc_delimiter);

    while (1) {
        bytes_read = getline(&line, &line_size, stdin);
        if (bytes_read == -1) {
            perror("getline");
            exit(1);
        }

        if (strcmp(line, heredoc_delimiter) == 0) {
            free(line);
            break;
        }

        if (write(fd, line, bytes_read) == -1) {
            perror("write");
            exit(1);
        }
    }

    free(line);
    close(fd);
}

void pipe_red(t_vars *vars) {
    int i = 0;
    const char *base_filename = "/tmp/heredoc"; 

    while (i < vars->n_commandes) {
        int j = 0;
        int fd = 0;
        if (vars->cmds[i].is_nex_pip) {
            pipe_commands(vars, i);
        }
        if (vars->cmds[i].has_redirections) {
            while (vars->cmds[i].opera_derec[j]) {
                if (!strcmp(vars->cmds[i].opera_derec[j], ">")) {
                    fd = open(vars->cmds[i].file_derec[j], O_CREAT | O_TRUNC | O_RDWR, 0644);
                    dup2(fd, 1);
                } else if (!strcmp(vars->cmds[i].opera_derec[j], "<")) {
                    fd = open(vars->cmds[i].file_derec[j], O_RDWR);
                    dup2(fd, 0);
                } else if (!strcmp(vars->cmds[i].opera_derec[j], ">>")) {
                    fd = open(vars->cmds[i].file_derec[j], O_CREAT | O_APPEND | O_RDWR, 0644);
                    dup2(fd, 1);
                } else if (!strcmp(vars->cmds[i].opera_derec[j], "<<")) {
    
                    if (j + 1 < MAX_REDIR && vars->cmds[i].file_derec[j + 1]) {
                        char *heredoc_delimiter = vars->cmds[i].file_derec[j + 1];

                        fd = create_temp_file(base_filename);
						
                        collect_and_write_heredoc(fd, heredoc_delimiter);

                        fd = create_temp_file(base_filename);
                        dup2(fd, 0);
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