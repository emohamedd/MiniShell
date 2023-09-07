/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haarab <haarab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:49:04 by haarab            #+#    #+#             */
/*   Updated: 2023/09/07 19:54:33 by haarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void run_echo (char **args)
{
    int i = 1;
    int check = 0;

    while (args[i])
    {
        if (ft_strncmp(args[i], "-n", ft_strlen("-n")) == 0)
        {
            check = 1;
            i++;
        }
        printf("%s ", args[i]);
        i++;
    }
    if (check == 0)
        printf("\n");
}
