/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 10:59:59 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/29 11:00:08 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strndup(char const *str, size_t max)
{
	size_t	index;
	char	*dst;

	index = 0;
	dst = malloc(sizeof(char) * (max + 1));
	// dst = malloc_((sizeof(char) * (max + 1)), NULL, 0, NULL);
	if (!dst)
	{
		return (0);
	}
	while (str[index] && index < max)
	{
		dst[index] = str[index];
		index++;
	}
	dst[index] = '\0';
	return (dst);
}