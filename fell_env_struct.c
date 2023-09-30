/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fell_env_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 10:59:43 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/30 22:32:10 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_x_dmax(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
}

char	*dp_en(const char *s1)
{
	int		i;
	char	*p;

	if (!s1)
		return (0);
	i = 0;
	p = malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (!p)
		return (NULL);
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

void	fell_env_struct(t_vars *vars)
{
	int		i;
	char	*key;
	char	**tempers;

	i = 0;
	tempers = NULL;
	while (vars->envp[i])
	{
		tempers = ft_split_export(vars->envp[i], '=');
		key = tempers[0];
		vars->env[i].key = dp_en(key);
		if (ft_strchr(vars->envp[i], '='))
		{
			vars->env[i].is_equal = 1;
			vars->env[i].value = dp_en(ft_strchr(vars->envp[i], '=') + 1);
		}
		if (tempers)
			free_x_dmax(tempers);
		tempers = NULL;
		i++;
	}
}
