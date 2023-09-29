/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haarab <haarab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 18:41:04 by haarab            #+#    #+#             */
/*   Updated: 2023/09/29 13:51:22 by haarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_oldpwd(t_vars *vars, char *pwd)
{
	int count = 0;
	while (count < vars->env_number)
	{
		if (ft_strncmp(vars->env[count].key, "OLDPWD", ft_strlen(vars->env[count].key) + 1) == 0)
		{
			vars->env[count].value = pwd;
		}
		count++;
	}
}

void	change_pwd(t_vars *vars, char *pwd)
{
	int count = 0;
	while (count < vars->env_number)
	{
		if (ft_strncmp(vars->env[count].key, "PWD", ft_strlen(vars->env[count].key) + 1) == 0)
		{
			vars->env[count].value = pwd;
		}
		count++;
	}
}


void ft_cd(t_vars *vars, char **args, char *pwd)
{
	if (chdir(args[1]) == -1)
	{
		ft_putendl_fd("minishell: No such file or directory", 2);
		exit_status = 1;
		return ;
	}
	if (vars->cmds[0].is_nex_pip)
	{
		exit_status = 0;
		return ;
	}
	change_oldpwd(vars, pwd);
	exit_status = 0;
}


void run_cd(char **args, t_vars *vars, char *pwd)
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
			exit_status = 1;
			return ;
		}
		chdir(ft_getenv("HOME", vars));
		change_oldpwd(vars, pwd);
		exit_status = 0;
	}
}
