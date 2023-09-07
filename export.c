/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haarab <haarab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:47:24 by haarab            #+#    #+#             */
/*   Updated: 2023/09/07 20:08:28 by haarab           ###   ########.fr       */
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
			printf("%s", vars->env[count].key);
			if (vars->env[count].is_equal)
			{
				printf("=");
				printf("\"%s\"""\n", vars->env[count].value);
			}
			count++;
		}
		return ;
	}
	count = 0;
	char *var_ = ft_split(args, '=')[0];
	while (count < vars->env_number) {
		if (!ft_strncmp(vars->env[count].key, var_, ft_strlen(var_))) {
			if (ft_strchr(args, '=') != NULL) {
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
	
	key = ft_split(args, '=')[0];
	vars->env[count].key = key;
	value = ft_strchr(args, '=') + 1;
	if (ft_strchr(args, '=') != NULL) {
		vars->env[count].is_equal = 1;
		vars->env[count].value = value;
	}
	free(tmp);
	vars->env_number++;
}