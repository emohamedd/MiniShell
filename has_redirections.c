/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 20:59:20 by haarab            #+#    #+#             */
/*   Updated: 2023/09/30 23:06:16 by emohamed         ###   ########.fr       */
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

int	handle_heredoc(char *delimiter)
{
	char	*base_filename;
	int		here_fd;

	if (delimiter)
	{
		base_filename = "emohamed";
		here_fd = create_temp_file(base_filename);
		if (here_fd != -1)
		{
			collect_and_write_heredoc(here_fd, delimiter);
			return (0);
		}
	}
	printf("syntax error near unexpected token\n");
	g_exit_status = 258;
	return (1);
}

int	has_redirections(t_vars *vars, int i)
{
	int	j;

	if (vars->cmds[i].has_redirections)
	{
		j = 0;
		while (vars->cmds[i].opera_derec[j])
		{
			if (!strcmp(vars->cmds[i].opera_derec[j], ">"))
				return (handle_output_redirection(vars->cmds[i].file_derec[j]));
			else if (!strcmp(vars->cmds[i].opera_derec[j], "<"))
				return (handle_input_redirection(vars->cmds[i].file_derec[j]));
			else if (!strcmp(vars->cmds[i].opera_derec[j], ">>"))
				return (handle_append_redirection(vars->cmds[i].file_derec[j]));
			else if (!strcmp(vars->cmds[i].opera_derec[j], "<<"))
				return (handle_heredoc(vars->cmds[i].file_derec[j]));
			j++;
		}
	}
	return (0);
}
