/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haarab <haarab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 20:59:20 by haarab            #+#    #+#             */
/*   Updated: 2023/09/27 15:49:34 by haarab           ###   ########.fr       */
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
	// rl_catch_signals = 1;
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

int	has_redirections(t_vars *vars, int i)
{
	int		j;
	int		fd;
	char	*base_filename;
	char	*heredoc_delimiter;
	
	fd = 0;
	base_filename = "emohamed";

	if (vars->cmds[i].has_redirections)
	{
		j = 0;
		while (vars->cmds[i].opera_derec[j])
		{
			if (!ft_strncmp(vars->cmds[i].opera_derec[j], ">", ft_strlen(">")
					+ 1))
			{
				if (vars->cmds[i].file_derec[j])
				{
					fd = open(vars->cmds[i].file_derec[j],
							O_CREAT | O_TRUNC | O_RDWR, 0644);
					dup2(fd, 1);
					close(fd);
				}
				else 
				{
					printf("syntax error near unexpected token\n");
					exit_status = 258;
					return (1);
				}
			}
			else if (!ft_strncmp(vars->cmds[i].opera_derec[j], "<",
					ft_strlen("<") + 1))
			{
				if (vars->cmds[i].file_derec[j])
				{
					fd = open(vars->cmds[i].file_derec[j], O_RDWR);
					dup2(fd, 0);
					close(fd);
				}
				else
				{
					printf("syntax error near unexpected token\n");
					exit_status = 258;
					return (1);
				}
			}
			else if (!ft_strncmp(vars->cmds[i].opera_derec[j], ">>",
					ft_strlen(">>") + 1))
			{
				if (vars->cmds[i].file_derec[j])
				{
					fd = open(vars->cmds[i].file_derec[j],
							O_CREAT | O_APPEND | O_RDWR, 0644);
					dup2(fd, 1);
					close(fd);
				}
				else
				{
					printf("syntax error near unexpected token\n");
					exit_status = 258;
					return (1);
				}
			}
			else if (!ft_strncmp(vars->cmds[i].opera_derec[j], "<<",
					ft_strlen("<<") + 1))
			{
				if (vars->cmds[i].file_derec[j])
				{
					heredoc_delimiter = vars->cmds[i].file_derec[j];
					vars->here_fd = create_temp_file(base_filename);
					collect_and_write_heredoc(vars->here_fd, heredoc_delimiter);
				}
				else
				{
					printf("syntax error near unexpected token\n");
					exit_status = 258;
					return (1);
				}
			}
			j++;
		}
	}
	return (0);
}
