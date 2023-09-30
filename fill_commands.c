/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 10:56:34 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/30 21:41:30 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	count_cmds(char **ptr, t_vars *vars)
{
	int	i;

	i = 0;
	vars->n_commandes = 1;
	while (ptr[i])
	{
		if (ptr[i + 1] && (ptr[i + 1][0] != '\0' 
			&& ft_strncmp("|", ptr[i + 1], ft_strlen(ptr[i + 1])) == 0))
			vars->n_commandes++;
		i++;
	}
}

void	allocat_cmds(t_vars *vars, char **ptr)
{
	int	i;
	int	b;

	i = 0;
	count_cmds(ptr, vars);
	vars->cmds = malloc_((sizeof(t_cmds) * (vars->n_commandes + 1)), NULL, 0,
			NULL);
	i = 0;
	b = 0;
	while (i < vars->n_commandes)
	{
		while (ptr[b] && (ft_strncmp("|", ptr[b], ft_strlen(ptr[b]))))
			b++;
		if (!ft_strncmp("|", ptr[b], ft_strlen(ptr[b])))
			b++;
		vars->cmds[i].cmds_args = malloc_((sizeof(char *) * (b + 1)), NULL, 0,
				NULL);
		i++;
	}
}

void	alocate_redirection(t_vars *vars, int i, int size_of_direc, int k)
{
	vars->cmds[i].cmds_args[k] = 0;
	if (size_of_direc > 0)
	{
		vars->cmds[i].opera_derec = get_redirectinsv(size_of_direc,
				vars->cmds[i].cmds_args);
		vars->cmds[i].file_derec = get_files(size_of_direc,
				vars->cmds[i].cmds_args);
		vars->cmds[i].has_redirections = 1;
		vars->cmds[i].cmds_args
			= clear_cmds_arg_from_direct(vars->cmds[i].cmds_args);
	}
	else
		vars->cmds[i].has_redirections = 0;
}

void	fell_redandpipe(t_vars *vars, char **ptr, t_int *intt, int i)
{
	vars->cmds[i].cmd = ptr[intt->b];
	while (ptr[intt->b] && ft_strncmp("|", ptr[intt->b],
			ft_strlen(ptr[intt->b])))
	{
		if (is_redirection(ptr[intt->b]))
			intt->size_of_direc++;
		vars->cmds[i].cmds_args[intt->k] = ptr[intt->b];
		intt->b++;
		intt->k++;
	}
	alocate_redirection(vars, i, intt->size_of_direc, intt->k);
	if (ptr[intt->b] && ptr[intt->b][0] != '\0' && (!ft_strncmp("|",
				ptr[intt->b], ft_strlen(ptr[intt->b]))))
	{
		vars->cmds[i].is_nex_pip = 1;
		intt->k++;
	}
	else
		vars->cmds[i].is_nex_pip = 0;
	intt->b++;
}

void	fill_commands(char **ptr, t_vars *vars)
{
	t_int	intt;
	int		i;

	intt.size_of_direc = 0;
	allocat_cmds(vars, ptr);
	i = 0;
	intt.b = 0;
	while (i < vars->n_commandes)
	{
		intt.k = 0;
		fell_redandpipe(vars, ptr, &intt, i);
		i++;
	}
}
