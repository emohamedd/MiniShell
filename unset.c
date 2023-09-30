/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:48:09 by haarab            #+#    #+#             */
/*   Updated: 2023/09/30 22:29:56 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_unset(char **args, t_vars *vars, int check)
{
	int		i;
	char	*key;

	i = 0;
	key = args[check];
	while (i < vars->env_number)
	{
		if (ft_strncmp(vars->env[i].key, key, ft_strlen(key) + 1) == 0)
		{
			free(vars->env[i].key);
			free(vars->env[i].value);
			while (i < vars->env_number)
			{
				vars->env[i] = vars->env[i + 1];
				i++;
			}
			vars->env_number--;
			g_exit_status = 0;
			return ;
		}
		i++;
	}
}
