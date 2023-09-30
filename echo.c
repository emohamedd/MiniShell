/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:49:04 by haarab            #+#    #+#             */
/*   Updated: 2023/09/30 16:13:29 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_n(char *args)
{
	int	i;

	i = 1;
	if (args[0] == '-')
	{
		if (args[0] == '-' && args[1] == '\0')
			return (1);
		if (args[1] != '\0')
		{
			while (args[i] && args[i] == 'n')
			{
				i++;
			}
		}
		if (args[i] == '\0')
			return (0);
	}
	return (1);
}

void	run_echo(char **args)
{
	int	i;
	int	check;
	int	j;

	i = 1;
	check = 0;
	while (args[i])
	{
		while (args[i] && check_n(args[i]) == 0)
		{
			check = 1;
			i++;
		}
		while (args[i])
		{
			j = 0;
			while (args[i][j])
			{
				if (args[i][j] == '$' && args[i][j + 1] == '?')
				{
					printf("%d", g_exit_status);
					j = j + 1;
				}
				else
					printf("%c", args[i][j]);
				j++;
			}
			if (args[i] != NULL && args[i + 1] != NULL)
				printf(" ");
			i++;
		}
		g_exit_status = 0;
	}
	if (check == 0)
		printf("\n");
}
