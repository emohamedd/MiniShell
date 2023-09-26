/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haarab <haarab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 18:41:04 by haarab            #+#    #+#             */
/*   Updated: 2023/09/26 03:11:07 by haarab           ###   ########.fr       */
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



void run_cd(char **args, t_vars *vars, char *pwd)
{
	if (args[1])
	{
		if (chdir(args[1]) == -1)
		{
			ft_putendl_fd("minishell: No such file or directory", 2);
			vars->exit_status = 1;
			return ;
		}
		if (ft_strncmp(args[1], "/", ft_strlen(args[1])) == 0 && vars->cmds[0].is_nex_pip)
		{
        	// chdir(args[1]);
			chdir(ft_getenv("HOME", vars));
			return ;
		}
		change_oldpwd(vars, pwd);
		vars->exit_status = 0;
	}
	else if (!args[1])
	{
		if (!ft_getenv("HOME", vars))
		{
			ft_putendl_fd("minishell: cd: HOME not set\n", 2);
			return ;
		}
		chdir(ft_getenv("HOME", vars));
		change_oldpwd(vars, pwd);
	}
}


// void run_cd(char **args, t_vars *vars)
// {
//     if (args[1])
// 	{
// 		if (ft_strncmp(args[1], "/", ft_strlen(args[1])) == 0)
// 		{
//         	// chdir(args[1]);
// 			chdir(ft_getenv("HOME", vars));
// 			return ;
// 		}
// 		else if (!ft_getenv("HOME", vars))
// 		{		
// 			printf ("minishell: No such file or directory\n");
// 			vars->exit_status = 1;
// 			return ;
// 		}
//         chdir(args[1]);
// 		vars->exit_status = 0;
// 	}
// 	else if (!args[1])
// 	{
// 		if (!ft_getenv("HOME", vars))
// 		{		
// 			printf ("minishell: cd: HOME not set\n");
// 			return ;
// 		}
// 		chdir(ft_getenv("HOME", vars));
// 	}
// }