/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:47:24 by haarab            #+#    #+#             */
/*   Updated: 2023/09/09 15:15:23 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void export_cmd(t_vars *vars, char *args)
{
	char *key;
	char *value;
    int count = 0;
	t_env *tmp = vars->env;
	count = 0;
	if (args == NULL)
	{
		while (count < vars->env_number)
		{
			if (vars->env[count].is_equal)
			{
				printf("%s%s", vars->env[count].key, GRN);
				printf("=");
				printf("\"%s%s\"""\n", vars->env[count].value, RED);
			}
			count++;
		}
		return ;
	}
	count = 0;
	char *var_ = ft_split(args, '=')[0];
	while (count < vars->env_number)
	{
		if (!ft_strncmp(vars->env[count].key, var_, ft_strlen(var_)))
		{
			if (ft_strchr(args, '=') != NULL)
			{
				vars->env[count].value = ft_strchr(args, '=') + 1;
				return;
			}
		}
		count++;
	}
	vars->env = malloc((vars->env_number + 1) * sizeof(t_env));
	count = 0;
	while (count < vars->env_number)
	{
		vars->env[count] = tmp[count];
		count++;
	}
	if (ft_isalpha(args[0]) == 1)
	{
		key = ft_split(args, '=')[0];
		vars->env[count].key = key;
		value = ft_strchr(args, '=') + 1;
		if (ft_strchr(args, '=') != NULL)
		{
			vars->env[count].is_equal = 1;
			vars->env[count].value = value;
		}
		vars->env_number++;
	}
	if (ft_isalpha(args[0]) != 1)
	{
		printf("`%s' : not a valid identifier\n", args);
	}
	free(tmp);
}