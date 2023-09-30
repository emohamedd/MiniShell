/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:49:04 by haarab            #+#    #+#             */
/*   Updated: 2023/09/30 21:38:18 by emohamed         ###   ########.fr       */
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

void	print_echo(char **args, int i)
{
	int	j;

	j = 0;
	while (args[i][j])
	{
		printf("%c", args[i][j]);
		j++;
	}
	if (args[i] != NULL && args[i + 1] != NULL)
		printf(" ");
}

void	run_echo(char **args)
{
	int	i;
	int	check;

	check = 0;
	i = 1;
	while (args[i])
	{
		while (args[i] && check_n(args[i]) == 0)
		{
			check = 1;
			i++;
		}
		if (args[i] && check_n(args[i]) == 1)
			g_exit_status = 0;
		while (args[i])
		{
			print_echo(args, i);
			i++;
		}
		g_exit_status = 0;
	}
	if (check == 0)
		printf("\n");
}
