/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haarab <haarab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 04:46:32 by haarab            #+#    #+#             */
/*   Updated: 2023/09/27 14:41:34 by haarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int is_numeric(const char *str) 
{
	int i = 0;
	while(str[i])
	{
		if (!ft_isdigit(str[i])) 
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
    if (i == 2 && is_numeric(str[1])) 
	{
        int res = atoi(str[1]);
        exit_status = res;
    } 
	else if (i == 2) 
	{
        printf("minishell: exit: %s: numeric argument required\n", str[1]);
        exit_status = 255;
    } 
	else if (i > 2) 
	{
        printf("minishell: exit: too many arguments\n");
        exit_status = 1;
    }
}



