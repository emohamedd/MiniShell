/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fell_env_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haarab <haarab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 10:59:43 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/29 15:45:59 by haarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fell_env_struct(t_vars *vars)
{
	int		i;
	char	*key;

	i = 0;
	while (vars->envp[i])
	{
		key = ft_split_export(vars->envp[i], '=')[0];
		vars->env[i].key = key;
		if (ft_strchr(vars->envp[i], '='))
		{
			vars->env[i].is_equal = 1;
			vars->env[i].value = ft_strchr(vars->envp[i], '=') + 1;
		}
		i++;
	}
}
