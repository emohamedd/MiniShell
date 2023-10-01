/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 20:59:20 by haarab            #+#    #+#             */
/*   Updated: 2023/10/01 09:02:04 by emohamed         ###   ########.fr       */
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
		free(read);
	}
	ft_putstr_fd(buff, 2);
	ft_putstr_fd(buff, fd);
	free(read);
}

int	redirect_heredoc(t_vars *vars, int j, char *base_filename, int i)
{
	char	*heredoc_delimiter;

	if (vars->cmds[i].file_derec[j])
	{
		heredoc_delimiter = vars->cmds[i].file_derec[j];
		vars->here_fd = create_temp_file(base_filename);
		collect_and_write_heredoc(vars->here_fd, heredoc_delimiter);
		rl_catch_signals = 0;
	}
	else
	{
		printf("syntax error near unexpected token\n");
		g_exit_status = 258;
		return (1);
	}
	return (0);
}

int	has_redirections(t_vars *vars, int i)
{
	int		j;
	char	*base_filename;

	base_filename = "emohamed";
	if (!vars->cmds[i].has_redirections)
		return (0);
	j = 0;
	while (vars->cmds[i].opera_derec[j])
	{
		if (!ft_strncmp(vars->cmds[i].opera_derec[j], ">", ft_strlen(">") + 1)
			&& redirect_output(vars, j, i))
			return (1);
		if (!ft_strncmp(vars->cmds[i].opera_derec[j], "<", ft_strlen("<") + 1)
			&& redirect_input(vars, j, i))
			return (1);
		if (!ft_strncmp(vars->cmds[i].opera_derec[j], ">>", ft_strlen(">>") + 1)
			&& redirect_output_append(vars, j, i))
			return (1);
		if (!ft_strncmp(vars->cmds[i].opera_derec[j], "<<", ft_strlen("<<") + 1)
			&& redirect_heredoc(vars, j, base_filename, i))
			return (1);
		j++;
	}
	return (0);
}
