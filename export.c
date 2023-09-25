/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haarab <haarab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:47:24 by haarab            #+#    #+#             */
/*   Updated: 2023/09/25 20:39:38 by haarab           ###   ########.fr       */
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

int check_doubelcouts(char *args)
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

void	export_cmd(t_vars *vars, char *args, char **str)
{
	char	*key;
	char	*value;
	int		count;
	t_env	*tmp;
	char	*var_;
	int		j;
	int		d; 
	int		p; 

	tmp = vars->env;
	count = 0;
	key = NULL;
	if (args == NULL)
	{
		while (count < vars->env_number)
		{
			if (vars->env[count].is_equal)
			{
				printf("declare -x %s", vars->env[count].key);
				printf("=");
				if (vars->env[count].value
					&& check_doubelcouts(vars->env[count].value) < 2)
				{
					printf("\"%s\"""\n", vars->env[count].value);
				}
				if (vars->env[count].value
					&& check_doubelcouts(vars->env[count].value) >= 2)
				{
					printf("%s\n", vars->env[count].value);
				}
				if (!vars->env[count].value)
					printf("");
			}
			if (!vars->env[count].is_equal)
			{
				printf("declare -x %s", vars->env[count].key);
				if (vars->env[count].value)
				{
					printf("=");
					printf("\"%s\"""", vars->env[count].value);
				}
				printf("\n");
				vars->exit_status = 0;
			}
			count++;
		}
		return ;
	}
	count = 0;
	var_ = ft_split(args, '=')[0];
	if (var_ == NULL)
		return ;
	if (check_key(var_) == 0)
	{
		printf("minishell: not a valid identifier\n");
		vars->exit_status = 1;
	}
	while (count < vars->env_number)
	{
		if (!ft_strncmp(vars->env[count].key, var_,
				ft_strlen(vars->env[count].key) + 1))
		{
			if (ft_strchr(args, '=') == NULL)
			{
				vars->env[count].value = vars->env[count].value;
				return ;
			}
			if (ft_strchr(args, '=') != NULL)
			{
				vars->env[count].value = ft_strchr(args, '=') + 1;
				return ;
			}
			j = 0;
			while (j < vars->env_number)
			{
				if (!ft_strncmp(vars->env[j].key, ft_strchr(args, '$') + 1,
						ft_strlen(vars->env[j].key) + 1))
				{
					vars->env[count].value = vars->env[j].value;
					return ;
				}
				j++;
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
	if (check_key(var_) == 1)
	{
		key = ft_split(args, '=')[0];
		d = 0;
		p = 0;
		while (vars->env[d].key)
		{
			if (ft_strncmp(vars->env[d].key, key, ft_strlen(vars->env[d].key)
					+ 1) == 0)
				p = 1;
			d++;
		}
		if (p != 1)
		{
			if (!ft_strchr(args, '$'))
			{
				vars->env[count].key = key;
				value = ft_strchr(args, '=') + 1;
				if (ft_strchr(args, '=') != NULL)
				{
					vars->env[count].is_equal = 1;
					vars->env[count].value = value;
				}
				if (!ft_strchr(args, '=') && p == 1)
				{
					vars->env[count].key = args;
				}
			}
			else if (ft_strchr(args, '$'))
			{
				vars->env[count].key = key;
				j = 0;
				while (j < vars->env_number)
				{
					if (!ft_strncmp(vars->env[j].key, ft_strchr(args, '$') + 1,
							ft_strlen(vars->env[j].key) + 1))
					{
						if (ft_strchr(args, '$') != NULL)
						{
							vars->env[count].value = vars->env[j].value;
							vars->env[count].is_equal = 1;
						}
					}
					j++;
				}
				if (!ft_strchr(args, '$') && p == 1)
				{
					vars->env[count].key = args;
				}
			}
			vars->env_number++;
		}
	}
	free(tmp);
}
