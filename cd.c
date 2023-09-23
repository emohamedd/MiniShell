/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haarab <haarab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 18:41:04 by haarab            #+#    #+#             */
/*   Updated: 2023/09/23 02:28:45 by haarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void run_cd(char **args, t_vars *vars)
// {
//     if (args[1])
// 	{
//         chdir(args[1]);
// 		vars->exit_status = 0;
// 		if (!ft_getenv("HOME", vars))
// 		{		
// 			printf ("minishell: No such file or directory\n");
// 			vars->exit_status = 1;
// 			return ;
// 		}
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


void run_cd(char **args, t_vars *vars)
{
    if (args[1])
	{
		if (ft_strncmp(args[1], "/", ft_strlen(args[1])) == 0)
		{
        	// chdir(args[1]);
			chdir(ft_getenv("HOME", vars));
			return ;
		}
		else if (!ft_getenv("HOME", vars))
		{		
			printf ("minishell: No such file or directory\n");
			vars->exit_status = 1;
			return ;
		}
        chdir(args[1]);
		vars->exit_status = 0;
	}
	else if (!args[1])
	{
		if (!ft_getenv("HOME", vars))
		{		
			printf ("minishell: cd: HOME not set\n");
			return ;
		}
		chdir(ft_getenv("HOME", vars));
	}
}