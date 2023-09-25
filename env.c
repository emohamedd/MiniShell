/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:33:44 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/25 15:30:13 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_cmd(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->env_number)
	{
		if (vars->env[i].is_equal)
		{
			printf("%s", vars->env[i].key);
			printf("=");
			printf("%s\n", vars->env[i].value);
		}
		i++;
	}
}
