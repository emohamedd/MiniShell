/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 04:46:32 by haarab            #+#    #+#             */
/*   Updated: 2023/09/24 12:51:16 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int is_numeric(const char *str) 
{
	int i = 0;
	while(str[i])
	{
		if (!isdigit(str[i])) 
		{
            return 0;
        }
		i++;
	}
    return 1;
}

void cmd_exit(char **str, t_vars *vars) 
{
    int i = 0;
    while (str[i]) 
	{
        i++;
    }
	if (!strncmp("exit", str[0], (ft_strlen(str[0]) + 1)))
	{
		ft_putstr_fd("exit\n", 2);
		vars->exit_status = 0;
		
	}
    if (i == 2 && is_numeric(str[1])) 
	{
        int res = atoi(str[1]);
        vars->exit_status = res;
    } 
	else if (i == 2) 
	{
        printf("minishell: exit: %s: numeric argument required\n", str[1]);
        vars->exit_status = 255;
    } 
	else if (i > 2) 
	{
        printf("minishell: exit: too many arguments\n");
        vars->exit_status = 1;
    }
}



