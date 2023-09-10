/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:49:04 by haarab            #+#    #+#             */
/*   Updated: 2023/09/10 12:52:37 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void run_echo (t_info **args)
{
    int i = 1;
    int check = 0;
    int g = 1;
    while ((*args)->size > i)
    {
        if (args[i])
            g = ft_strncmp(args[i]->content, "-n", ft_strlen("-n"));
        if (g == 0)
        {
            check = 1;
            i++;
        }
        if (args[i])
            printf("%s ", args[i]->content);
        i++;
    }
    if (check == 0)
        printf("\n");
}
