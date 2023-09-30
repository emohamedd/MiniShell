/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 17:01:08 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/30 05:01:15 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_err(char **args)
{
	if (syntax_errors(args) > 0)
	{
		printf("minishell: syntax error\n");
		exit_status = 2;
		return (1);
	}
	return (0);
}
