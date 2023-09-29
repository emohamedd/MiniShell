/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haarab <haarab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 17:01:08 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/29 18:44:55 by haarab           ###   ########.fr       */
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