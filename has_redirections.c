/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 20:59:20 by haarab            #+#    #+#             */
/*   Updated: 2023/09/29 13:04:35 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_temp_file(char *base_filename)
{
	int	fd;

	fd = open(base_filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (fd == -1)
	{
		perror("open");
		exit(1);
	}
	return (fd);
}

void	collect_and_write_heredoc(int fd, char *heredoc_delimiter)
{
	char	*read;
	char	*buff;
	char	*line;

	read = NULL;
	buff = "";
	rl_catch_signals = 1;
	while (1)
	{
		read = readline("> ");
		if (!read)
			return ;
		if (ft_strcmp(read, heredoc_delimiter) == 0)
			break ;
		buff = ft_strjoin(buff, read);
		buff = ft_strjoin(buff, "\n");
	}
	ft_putstr_fd(buff, 2);
	ft_putstr_fd(buff, fd);
}

int handle_output_redirection(char *filename) {
    if (filename) {
        int fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
        if (fd != -1) {
            dup2(fd, 1);
            close(fd);
            return 0; // Success
        }
    }
    printf("syntax error near unexpected token\n");
    exit_status = 258;
    return 1; // Failure
}

int handle_input_redirection(char *filename) {
    if (filename) {
        int fd = open(filename, O_RDWR);
        if (fd != -1) {
            dup2(fd, 0);
            close(fd);
            return 0; // Success
        }
    }
    printf("syntax error near unexpected token\n");
    exit_status = 258;
    return 1; // Failure
}

int handle_append_redirection(char *filename) {
    if (filename) {
        int fd = open(filename, O_CREAT | O_APPEND | O_RDWR, 0644);
        if (fd != -1) {
            dup2(fd, 1);
            close(fd);
            return 0; // Success
        }
    }
    printf("syntax error near unexpected token\n");
    exit_status = 258;
    return 1; // Failure
}

int handle_heredoc( char *delimiter) 
{
    if (delimiter) 
	{
        char *base_filename = "emohamed";
        int here_fd = create_temp_file(base_filename);
        if (here_fd != -1) 
		{
            collect_and_write_heredoc(here_fd, delimiter);
            return 0; // Success
        }
    }
    printf("syntax error near unexpected token\n");
    exit_status = 258;
    return 1; // Failure
}

int has_redirections(t_vars *vars, int i) 
{
    if (vars->cmds[i].has_redirections) 
	{
        int j = 0;
        while (vars->cmds[i].opera_derec[j]) 
		{
            if (!strcmp(vars->cmds[i].opera_derec[j], ">")) 
			{
                return handle_output_redirection(vars->cmds[i].file_derec[j]);
            } 
			else if (!strcmp(vars->cmds[i].opera_derec[j], "<")) 
			{
                return handle_input_redirection(vars->cmds[i].file_derec[j]);
            } 
			else if (!strcmp(vars->cmds[i].opera_derec[j], ">>")) 
			{
                return handle_append_redirection(vars->cmds[i].file_derec[j]);
            } 
			else if (!strcmp(vars->cmds[i].opera_derec[j], "<<")) 
			{
                return handle_heredoc(vars->cmds[i].file_derec[j]);
            }
            j++;
        }
    }
    return 0; // No redirections found
}