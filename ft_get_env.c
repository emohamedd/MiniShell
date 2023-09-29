/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 10:59:01 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/25 15:44:42 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char *key, t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->env_number)
	{
		if (!ft_strncmp(vars->env[i].key, key, ft_strlen(vars->env[i].key)))
		{
			return (vars->env[i].value);
		}
		i++;
	}
	return (NULL);
}
