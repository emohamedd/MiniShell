/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haarab <haarab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:47:24 by haarab            #+#    #+#             */
/*   Updated: 2023/09/09 22:33:24 by haarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_equal(char *args)
{
	if (args[0] == '=' && args[1] == '\0')
	{
		printf ("export: `%s' : not a valid identifier\n", args);
		return (1);
	}
	return (0);
}



void export_cmd(t_vars *vars, char *args)
{
	char *key = NULL;
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
				if (vars->env[count].value)
					printf("\"%s%s\"""\n", vars->env[count].value, RED);
				else if(!vars->env[count].value)
					printf("");
			}
			if (!vars->env[count].is_equal)
			{
				printf("%s%s", vars->env[count].key, GRN);
				if (vars->env[count].value)
				{
					printf("=");
					printf("\"%s%s\"""", vars->env[count].value, RED);
				}
				printf("\n");
			}
			count++;
		}
		return ;
	}
	count = 0;
	char *var_ = ft_split(args, '=')[0];
	if (var_ == NULL)
		return ;
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
		// else if (vars->env[count].key == key && value == NULL)
		// {
		// 	vars->env[count].is_equal = 1;
		// 	vars->env[count].value = value;
		// }
		vars->env_number++;
	}
	if (!ft_strchr(args, '='))
	{
		vars->env[count].key = args;
	}
	if (ft_isalpha(args[0]) != 1)
	{
		printf("export : `%s' : not a valid identifier\n", args);
	}
	free(tmp);
	
}