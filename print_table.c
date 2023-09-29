/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_table.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 16:54:29 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/25 15:50:48 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	table(char **str, t_info **tokens)
{
	int	i;

	i = 0;
	printf("+%s--------------------------------------------------------------+|%s\n",
		PURPLE, RESET);
	printf("|     %sTOKEN         |       LENGHT     |     %sTYPE    %s\n",
		GREEN, GREEN, GREEN);
	printf("+%s--------------------------------------------------------------+|%s\n",
		PURPLE, RESET);
	while (str[i])
	{
		printf("    %s%s%s           |         %d%s        |      %s\n", YELLOW,
			tokens[i]->content, YELLOW, tokens[i]->lenght, YELLOW,
			tokens[i]->type);
		printf("+%s--------------------------------------------------------------+|%s\n",
			PURPLE, RESET);
		i++;
	}
}
