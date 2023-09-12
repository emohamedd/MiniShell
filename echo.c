/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haarab <haarab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:49:04 by haarab            #+#    #+#             */
/*   Updated: 2023/09/12 21:19:25 by haarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_n(char *args)
{
	int i = 1;
	if (args[0] == '-')
	{
		if (args[0] == '-' && args[1] == '\0')
			return (1);
		if (args[1] != '\0')
		{
			while (args[i] == 'n')
			{
				i++;
			}
		}
		if (args[i] == '\0')
			return (0);
	}
	return (1);
}

void run_echo (char **args, t_vars *vars)
{
    int i = 1;
    int check = 0;

	// if (ft_strncmp((args[1]), "$?", ft_strlen("$?") == 0))
	// {
	// 		// printf ("hamza\n");
	// 		printf ("%d\n", vars->exit_status);
	// 		return ;
	// }
    while (args[i])
    {
        while (check_n(args[i]) == 0)
        {
            check = 1;
            i++;
        }
		if (check_n(args[i]) == 1)
			vars->exit_status = 0;
        while (args[i])
		{
            printf("%s", args[i]);
			if (args[i] != NULL && args[i + 1] != NULL)
				printf(" ");
        	i++;
		}
    }
    if (check == 0)
        printf("\n");
}
