/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_types.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 17:05:12 by emohamed          #+#    #+#             */
/*   Updated: 2023/10/01 00:05:10 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_output(t_vars *vars, int j, int i)
{
	int	fd;

	if (vars->cmds[i].file_derec[j])
	{
		fd = open(vars->cmds[i].file_derec[j], O_CREAT | O_TRUNC | O_RDWR,
				0644);
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

int	redirect_input(t_vars *vars, int j, int i)
{
	int	fd;

	if (vars->cmds[i].file_derec[j])
	{
		fd = open(vars->cmds[i].file_derec[j], O_RDWR);
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

int	redirect_output_append(t_vars *vars, int j, int i)
{
	int	fd;

	if (vars->cmds[i].file_derec[j])
	{
		fd = open(vars->cmds[i].file_derec[j], O_CREAT | O_APPEND | O_RDWR,
				0644);
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
