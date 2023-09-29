/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haarab <haarab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:47:24 by haarab            #+#    #+#             */
/*   Updated: 2023/09/29 15:05:34 by haarab           ###   ########.fr       */
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


void print_env_equal(t_vars *vars, int count)
{
	printf("declare -x %s", vars->env[count].key);
	printf("=");
	if (vars->env[count].value
		&& check_doubelcouts(vars->env[count].value) < 2)
		printf("\"%s\"""\n", vars->env[count].value);
	if (vars->env[count].value
		&& check_doubelcouts(vars->env[count].value) >= 2)
		printf("%s\n", vars->env[count].value);
	if (!vars->env[count].value)
		printf("");
}

void print_env(t_vars *vars, int count)
{
	while (count < vars->env_number)
	{
		if (vars->env[count].is_equal)
			print_env_equal(vars, count);
		if (!vars->env[count].is_equal)
		{
			printf("declare -x %s", vars->env[count].key);
			if (vars->env[count].value)
			{
				printf("=");
				printf("\"%s\"""", vars->env[count].value);
			}
			printf("\n");
		}
		count++;
	}
}

// int fell_value(t_vars *vars)


int fell_env_value(t_vars *vars,char *args, int count, char *var_)
{
	int j;
	
	if (!ft_strncmp(vars->env[count].key, var_,
				ft_strlen(vars->env[count].key) + 1))
	{
		if (ft_strchr(args, '=') == NULL)
		{
			vars->env[count].value = vars->env[count].value;
			exit_status = 0;
			return (0);
		}
		if (ft_strchr(args, '=') != NULL)
		{
			vars->env[count].value = ft_strchr(args, '=') + 1;
			exit_status = 0;
			return (0);
		}
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
	char *value;
	
	value = ft_strchr(args, '=') + 1;
	if (ft_strchr(args, '=') != NULL)
	{
		vars->env[count].is_equal = 1;
		vars->env[count].value = value;
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
	char *value;
	int j;

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
				exit_status = 0;
			}
		}
		j++;
	}
	if (!ft_strchr(args, '$') && p == 1)
	{
		vars->env[count].key = args;
		exit_status = 0;
	}
}



void	fell_env(t_vars *vars, int count, char *args, char *key, int p)
{
	int j;
	char *value;
	if (!ft_strchr(args, '$'))
	{
		vars->env[count].key = key;
		fell_env_isequal(vars, count, args, p);
	}
	else if (ft_strchr(args, '$'))
	{
		vars->env[count].key = key;
	}
}

void fell_envirement(t_vars *vars, int count, char *args, char *key)
{
	int p;
	int d;
	int x;
	
	p = 0;
	d = 0;
	key = ft_split_export(args, '=')[0];
	x = 0;
	while (x < vars->env_number)
	{
		if (vars->env[d].key) {
			if (ft_strcmp(vars->env[d].key, key) == 0)
				p = 1;
		}
		d++;
		x++;
	}
	if (p != 1)
	{
		fell_env(vars, count, args, key, p);
		vars->env_number++;
	}
}

int count_env(t_vars *vars, t_env *tmp)
{
	int count;
	
	count = 0;
	while (count < vars->env_number)
	{
		vars->env[count] = tmp[count];
		count++;
	}
	return (count);
}

int export_env(t_vars *vars, char *var_, char *args)
{
	int count;

	count = 0;
	if (var_ == NULL)
		return (0);
	if (check_key(var_) == 0)
	{
		printf("minishell: not a valid identifier\n");
		exit_status = 1;
	}
	count = 0;
	while (count < vars->env_number)
	{
		if (fell_env_value(vars, args, count, var_) == 0)
			return (0);
		count++;
	}
	return (1);
}


void	export_cmd(t_vars *vars, char *args, char **str)
{
	char	*key;
	char	*value;
	int		count;
	t_env	*tmp;
	char	*var_;

	tmp = vars->env;
	count = 0;
	key = NULL;
	if (args == NULL)
	{
		print_env(vars, count);
		return ;
	}
	var_ = ft_split_export(args, '=')[0];
	if (export_env(vars, var_, args) == 0)
		return ;
	vars->env = malloc((vars->env_number + 1) * sizeof(t_env));
	count = count_env(vars, tmp);
	if (check_key(var_) == 1)
		fell_envirement(vars, count, args, key);
	free(tmp);
}
