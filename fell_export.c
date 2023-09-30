/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fell_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haarab <haarab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 17:05:43 by haarab            #+#    #+#             */
/*   Updated: 2023/09/30 17:52:23 by haarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fell_value(t_vars *vars, char *args, int count)
{
	if (ft_strchr(args, '=') == NULL)
	{
		vars->env[count].value = vars->env[count].value;
		exit_status = 0;
		return (0);
	}
	if (ft_strchr(args, '=') != NULL)
	{
		free(vars->env[count].value);
		vars->env[count].value = ft_strdup_env(ft_strchr(args, '=') + 1);
		exit_status = 0;
		return (0);
	}
	return (1);
}

int	fell_env_value(t_vars *vars, char *args, int count, char *var_)
{
	int	j;

	if (!ft_strncmp(vars->env[count].key, var_, ft_strlen(vars->env[count].key)
			+ 1))
	{
		if (fell_value(vars, args, count) == 0)
			return (0);
		j = 0;
		while (j < vars->env_number)
		{
			if (!ft_strncmp(vars->env[j].key, ft_strchr(args, '$') + 1,
					ft_strlen(vars->env[j].key) + 1))
			{
				vars->env[count].value = vars->env[j].value;
				exit_status = 0;
				return (0);
			}
			j++;
		}
	}
	return (1);
}

void	fell_env_isequal(t_vars *vars, int count, char *args, int p)
{
	char	*value;

	value = ft_strchr(args, '=') + 1;
	if (ft_strchr(args, '=') != NULL)
	{
		vars->env[count].is_equal = 1;
		vars->env[count].value = ft_strdup_env(value);
		exit_status = 0;
	}
	if (!ft_strchr(args, '=') && p == 1)
	{
		vars->env[count].key = args;
		exit_status = 0;
	}
}

void	fell_env_dollar(t_vars *vars, int count, char *args, int p)
{
	int		j;

	j = 0;
	while (j < vars->env_number)
	{
		if (!ft_strncmp(vars->env[j].key, ft_strchr(args, '$') + 1,
				ft_strlen(vars->env[j].key) + 1))
		{
			if (ft_strchr(args, '$') != NULL)
			{
				vars->env[count].value = ft_strdup_env(vars->env[j].value);
				vars->env[count].is_equal = 1;
				exit_status = 0;
			}
		}
		j++;
	}
	if (p == 1)
	{
		vars->env[count].key = args;
		exit_status = 0;
	}
}

void	fell_env(t_vars *vars, char *args, char *key, t_export	*export_int)
{
	if (!ft_strchr(args, '$'))
	{
		vars->env[export_int->count].key = key;
		fell_env_isequal(vars, export_int->count, args, export_int->p);
	}
	else if (ft_strchr(args, '$'))
	{
		vars->env[export_int->count].key = key;
	}
}
