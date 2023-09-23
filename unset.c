/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haarab <haarab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:48:09 by haarab            #+#    #+#             */
/*   Updated: 2023/09/23 01:13:49 by haarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void check_unset(char **args, t_vars *vars, int check)
{
	int i = 0;
	char *key;

	key = args[check];
	while (i < vars->env_number)
	{
		if (ft_strncmp(vars->env[i].key, key, ft_strlen(key) + 1) == 0)
		{
			while (i < vars->env_number)
			{
				vars->env[i] = vars->env[i + 1];
				i++;
			}
			vars->env_number--;
			return;
		}
		i++;
	}
}