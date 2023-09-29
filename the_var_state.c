/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_var_state.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 11:01:16 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/29 11:01:38 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_var_inside_sq(char *arg, int index) 
{
	int count = 0;
	int count_sq = 0;
	int count_dq = 0;
	while (arg[count]) {
		if (arg[count] == '\'' && count_dq % 2 == 0)
			count_sq++;
		if (arg[count] == '\"')
			count_dq++;
		if (count == index && count_sq % 2 == 0)
			return 0;
		else if (count == index && count_sq % 2 != 0)
			return 1;
		count++;
	}
	return 0;
}
