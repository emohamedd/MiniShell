/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haarab <haarab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 04:46:32 by haarab            #+#    #+#             */
/*   Updated: 2023/09/23 06:09:08 by haarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void cmd_exit(char **str, t_vars *vars)
{
	int i = 0;
	while (str[i])
	{
		i++;
	}
	if (i == 2)
	{
		int res = ft_atoi(str[1]);
		vars->exit_status = res;
	}
	if (i > 2)
	{
		i = 1;
		int j = 0;
		while ((str[i][j] >= '0' && str[i][j] <= '9') || (str[i][j] >= 'a' && str[i][j] <= 'z'))
		{
			if (str[i][j] >= '0' && str[i][j] <= '9')
			{
				j++;
			}
			else
			{
				printf ("minishell: exit: %s: numeric argument required\n", str[i]);
				vars->exit_status = 255;
			}
			if (str[i][j] == '\0')
			{
				printf ("minishell: exit: too many arguments\n");
				vars->exit_status = 1;
			}
			j++;
		}
	}
	
}