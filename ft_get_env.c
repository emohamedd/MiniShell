/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haarab <haarab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 10:59:01 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/23 01:19:50 by haarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_getenv(char *key, t_vars *vars)
{
	int i;
	i = 0;
	while (i < vars->env_number) 
	{
		if (!ft_strncmp(vars->env[i].key, key, ft_strlen(vars->env[i].key)))
		{
			return (vars->env[i].value);
		}
		i++;
	}
	return NULL;
}