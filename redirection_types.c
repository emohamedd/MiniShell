/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_types.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 17:05:12 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/30 19:57:29 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int	handle_output_redirection(char *filename)
{
	int	fd;

	if (filename)
	{
		fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
		dup2(fd, 1);
		close(fd);
	}
	else
	{
		printf("syntax error near unexpected token\n");
		g_exit_status = 258;
		return (1);
	}
	return (0);
}

int	handle_input_redirection(char *filename)
{
	int	fd;
	if (!(access(filename, F_OK)))
	{
		if (filename)
		{
			fd = open(filename, O_RDWR);
			dup2(fd, 0);
			close(fd);
		}
		else
		{
			printf("syntax error near unexpected token\n");
			g_exit_status = 258;
			return (1);
		}
		return (0);
	}
	else
	{
		write(2, "No such file or directory\n", 26);
		g_exit_status = 1;
		return (1);
	}
	return (0);
}

int	handle_append_redirection(char *filename)
{
	int	fd;

	if (filename)
	{
		fd = open(filename, O_CREAT | O_APPEND | O_RDWR, 0644);
		dup2(fd, 1);
		close(fd);
	}
	else
	{
		printf("syntax error near unexpected token\n");
		g_exit_status = 258;
		return (1);
	}
	return (0);
}
