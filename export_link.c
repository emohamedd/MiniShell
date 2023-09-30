/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_link.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haarab <haarab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 16:59:13 by haarab            #+#    #+#             */
/*   Updated: 2023/09/30 17:51:44 by haarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_key(char *args)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (args[i])
	{
		if ((args[i] >= 'a' && args[i] <= 'z') || (args[i] >= 'A'
				&& args[i] <= 'Z') || args[i] == '_')
			j++;
		if (i > 0)
			if ((args[i] >= '0' && args[i] <= '9'))
				j++;
		i++;
	}
	if (args[j] == '\0')
		return (1);
	return (0);
}

int	check_doubelcouts(char *args)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (args[i])
	{
		if (args[i] == 34)
		{
			count++;
		}
		i++;
	}
	return (count);
}

void	print_env_equal(t_vars *vars, int count)
{
	printf("declare -x %s", vars->env[count].key);
	printf("=");
	if (vars->env[count].value && check_doubelcouts(vars->env[count].value) < 2)
		printf("\"%s\"""\n", vars->env[count].value);
	if (vars->env[count].value
		&& check_doubelcouts(vars->env[count].value) >= 2)
		printf("%s\n", vars->env[count].value);
	if (!vars->env[count].value)
		printf("");
}

void	print_env(t_vars *vars, int count)
{
	while (count < vars->env_number)
	{
		printf("declare -x %s", vars->env[count].key);
		if (vars->env[count].value)
		{
			printf("=");
			printf("\"%s\"", vars->env[count].value);
		}
		printf("\n");
		count++;
	}
}
