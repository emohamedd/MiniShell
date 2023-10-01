/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 18:41:04 by haarab            #+#    #+#             */
/*   Updated: 2023/10/01 09:40:49 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_oldpwd(t_vars *vars, char *pwd)
{
	int	count;

	count = 0;
	while (count < vars->env_number)
	{
		if (ft_strncmp(vars->env[count].key, "OLDPWD",
				ft_strlen(vars->env[count].key) + 1) == 0)
		{
			free(vars->env[count].value);
			vars->env[count].value = dp_en(pwd);
		}
		count++;
	}
}

void	change_pwd(t_vars *vars, char *pwd)
{
	int	count;

	count = 0;
	while (count < vars->env_number)
	{
		if (ft_strncmp(vars->env[count].key, "PWD",
				ft_strlen(vars->env[count].key) + 1) == 0)
		{
			free(vars->env[count].value);
			vars->env[count].value = dp_en(pwd);
		}
		count++;
	}
}

void	ft_cd(t_vars *vars, char **args, char *pwd)
{
	if (chdir(args[1]) == -1)
	{
		ft_putendl_fd("minishell: No such file or directory", 2);
		g_exit_status = 1;
		return ;
	}
	if (vars->cmds[0].is_nex_pip)
	{
		g_exit_status = 0;
		return ;
	}
	change_oldpwd(vars, pwd);
	g_exit_status = 0;
}

void	run_cd(char **args, t_vars *vars, char *pwd)
{
	if (args[1])
	{
		ft_cd(vars, args, pwd);
	}
	else if (!args[1])
	{
		if (!ft_getenv("HOME", vars))
		{
			ft_putendl_fd("minishell: cd: HOME not set", 2);
			g_exit_status = 1;
			return ;
		}
		chdir(ft_getenv("HOME", vars));
		change_oldpwd(vars, pwd);
		g_exit_status = 0;
	}
}
