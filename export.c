/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:47:24 by haarab            #+#    #+#             */
/*   Updated: 2023/09/30 22:32:10 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fell_envirement(t_vars *vars, int count, char *args, char *key)
{
	t_export	export_int;
	char		**tempers;

	export_int.p = 0;
	export_int.d = 0;
	tempers = ft_split_export(args, '=');
	key = dp_en(tempers[0]);
	export_int.x = 0;
	while (export_int.x < vars->env_number)
	{
		if (vars->env[export_int.d].key)
		{
			if (ft_strcmp(vars->env[export_int.d].key, key) == 0)
				export_int.p = 1;
		}
		export_int.d++;
		export_int.x++;
	}
	if (export_int.p != 1)
	{
		export_int.count = count;
		fell_env (vars, args, key, &export_int);
		vars->env_number++;
	}
	free_x_dmax(tempers);
}

int	count_env(t_vars *vars, t_env *tmp)
{
	int	count;

	count = 0;
	while (count < vars->env_number)
	{
		vars->env[count] = tmp[count];
		count++;
	}
	return (count);
}

int	export_env(t_vars *vars, char *var_, char *args)
{
	int	count;

	count = 0;
	if (var_ == NULL)
		return (0);
	if (check_key(var_) == 0)
	{
		printf("minishell: not a valid identifier\n");
		g_exit_status = 1;
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

int	print_export(t_vars *vars, char *args, int count)
{
	if (args == NULL)
	{
		print_env(vars, count);
		return (0);
	}
	if (args[0] == '=')
	{
		printf ("minishell: export: `%s': not a valid identifier\n", args);
		g_exit_status = 1;
		return (0);
	}
	return (1);
}

void	export_cmd(t_vars *vars, char *args)
{
	char	*key;
	int		count;
	t_env	*tmp;
	char	*var_;
	char	**tempers;

	count = 0;
	if (print_export(vars, args, count) == 0)
		return ;
	key = NULL;
	tmp = vars->env;
	tempers = ft_split_export(args, '=');
	var_ = tempers[0];
	if (export_env(vars, var_, args) == 0)
	{
		free_x_dmax(tempers);
		return ;
	}
	vars->env = malloc((vars->env_number + 1) * sizeof(t_env));
	count = count_env(vars, tmp);
	if (check_key(var_) == 1)
		fell_envirement(vars, count, args, key);
	free_x_dmax(tempers);
	free(tmp);
}
