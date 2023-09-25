/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 10:56:34 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/25 15:43:35 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_commands(char **ptr, t_vars *vars)
{
	int	i;
	int	j;
	int	l;
	int	h;
	int	b;
	int	k;
	int	size_of_direc;

	i = 0;
	j = 0;
	l = 1;
	while (ptr[i])
	{
		if (ptr[i + 1] && (ft_strncmp("|", ptr[i + 1], ft_strlen(ptr[i + 1])) == 0))
			l++;
		i++;
	}
	vars->cmds = malloc(sizeof(t_cmds) * (l + 1));
	i = 0;
	h = 0;
	b = 0;
	while (i < l)
	{
		while (ptr[b] && (ft_strncmp("|", ptr[b], ft_strlen(ptr[b]))))
			b++;
		if (!ft_strncmp("|", ptr[b], ft_strlen(ptr[b])))
			b++;
		vars->cmds[i].cmds_args = malloc(sizeof(char *) * (b + 1));
		i++;
	}
	i = 0;
	b = 0;
	k = 0;
	size_of_direc = 0;
	while (i < l)
	{
		size_of_direc = 0;
		k = 0;
		vars->cmds[i].cmd = ptr[b];
		while (ptr[b] && ft_strncmp("|", ptr[b], ft_strlen(ptr[b])))
		{
			if (is_redirection(ptr[b]))
				size_of_direc++;
			vars->cmds[i].cmds_args[k] = ptr[b];
			b++;
			k++;
		}
		vars->cmds[i].cmds_args[k] = 0;
		if (size_of_direc > 0)
		{
			vars->cmds[i].opera_derec = get_redirectinsv(size_of_direc,
					vars->cmds[i].cmds_args);
			vars->cmds[i].file_derec = get_files(size_of_direc,
					vars->cmds[i].cmds_args);
			vars->cmds[i].has_redirections = 1;
			vars->cmds[i].cmds_args = clear_cmds_arg_from_direct(vars->cmds[i].cmds_args);
		}
		else
			vars->cmds[i].has_redirections = 0;
		if (ptr[b] && !ft_strncmp("|", ptr[b], ft_strlen(ptr[b])))
		{
			vars->cmds[i].is_nex_pip = 1;
			k++;
		}
		else
			vars->cmds[i].is_nex_pip = 0;
		b++;
		i++;
	}
	vars->n_commandes = l;
}
