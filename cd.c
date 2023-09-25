/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haarab <haarab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 18:41:04 by haarab            #+#    #+#             */
/*   Updated: 2023/09/25 20:51:06 by haarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void run_cd(char **args, t_vars *vars)
{
	if (args[1])
	{
		if (chdir(args[1]) == -1)
		{
			ft_putendl_fd("minishell: cd: no such file or directory", 2);
			return ;
		}
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
	}
}
