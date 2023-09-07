/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haarab <haarab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:47:45 by haarab            #+#    #+#             */
/*   Updated: 2023/09/07 19:54:41 by haarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void env_cmd(t_vars *vars)
{
    int i = 0;
    while (i < vars->env_number)
	{
        if (vars->env[i].is_equal)
		{
            printf("%s", vars->env[i].key);
            printf("=");
            printf("%s\n", vars->env[i].value);
        }
        i++;
    }
}