/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:47:24 by haarab            #+#    #+#             */
/*   Updated: 2023/09/11 14:40:09 by emohamed         ###   ########.fr       */
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

char *skip_quots(char *str)
{
	int i = 0;
	int j = 0;
	if (!str)
		return (NULL);
	while(str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			j++;
		i++;
	}
	char *ptr = malloc(sizeof(char *) * ft_strlen(str) - j + 1);
	i = 0;
	j = 0;
	while(str[i])
	{
		if (str[i] != 34 && str[i] != 39)
		{
			ptr[j] = str[i];
			j++;
		}
		i++;
	}
	ptr[j] = '\0';
	free(str);
	return (ptr);
}

char *skip_quotsinquots(char *str)
{
	int i = 0;
	int j = 0;
	if (!str)
		return (NULL);
	char *ptr = NULL;
	while (str[i])
	{
		if (str[i] != 34 && str[i] != 39)
		{
			j++;
		}
		i++;
	}
	ptr = malloc(sizeof(char) * ft_strlen(str) - j + 1);
	// if (!ptr)
	// 	return (NULL);
	// // printf("%s == %d\n", str, k);
	int k = ft_strlen(str);
	i = 0;
	j = 0;
	while(i < k)
	{
		if (str[i] != 34 && str[i] != 39)
		{
			ptr[j] = str[i];
			j++;
		}
		i++;
	}
	ptr[j] = '\0';
	return (ptr);
}

int check_doubelcouts(char *args)
{
	int i;
	
	i = 0;
	int count = 0;
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

void export_cmd(t_vars *vars, char *args)
{
	char *key = NULL;
	char *value;
    int count = 0;
	t_env *tmp = vars->env;
	count = 0;
	// char *str; 
	if (args == NULL)
	{
		while (count < vars->env_number)
		{
			if (vars->env[count].is_equal)
			{
				printf("%s", vars->env[count].key );
				printf("=");
				if (vars->env[count].value && check_doubelcouts(vars->env[count].value) < 2)
				{
					// int sss = check_doubelcouts(vars->env[count].value);
					// printf("%d", sss);
					printf("\"%s\"""\n", vars->env[count].value);
				}
				if (vars->env[count].value && check_doubelcouts(vars->env[count].value) >= 2)
				{
					// int sss = check_doubelcouts(vars->env[count].value);
					// printf("%d", sss);
					printf("%s\n", vars->env[count].value);
				}
				if(!vars->env[count].value)
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
		vars->env[count].key = skip_quots(key);
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