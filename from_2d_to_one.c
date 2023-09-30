/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   from_2d_to_one.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 10:57:21 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/30 01:45:07 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*swap(char **str)
{
	int		i;
	char	*s;

	i = 0;
	s = NULL;
	while (str[i])
	{
		s = ft_strjoin(s, str[i]);
		i++;
		if (str[i])
			s = ft_strjoin(s, " ");
	}
	return (s);
}
