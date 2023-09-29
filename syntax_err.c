/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haarab <haarab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 17:01:08 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/28 21:52:45 by haarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int syntax_err(char **args, t_vars *vars)
{
	// if (command_notfound(args, vars) > 0)
	// {
	// 	printf ("minishell: command not found\n");
	// 	exit_status = 0;
	// 	return (1);
	// }
	if (syntax_errors(args, vars) > 0)
	{
		printf ("minishell: syntax error\n");
		exit_status = 2;
		return (1);
	}
	return (0);
}

int double_quotes(char **args)
{
	int j;
	int quotes;
	int i = 0;
	while(args[i])
	{
		j = 0;
		quotes = 0;
		while (args[i][j])
		{
			if (args[i][j] == 34)
			{
				quotes++;
			}
			j++;
		}
		printf ("str == %d\n", quotes);
		if (quotes % 2 != 0)
		{
			printf ("minishell: unexpected EOF while looking for matching\n");
			exit_status = 2;
			return (1);
		}
		i++;
	}
	return (0);
}