/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haarab <haarab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 10:59:59 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/30 18:46:32 by haarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strndup(char const *str, size_t max)
{
	size_t	index;
	char	*dst;

	index = 0;
	dst = malloc_(sizeof(char) * (max + 1), NULL, 0, NULL);
	if (!dst)
		return (0);
	while (str[index] && index < max)
	{
		dst[index] = str[index];
		index++;
	}
	dst[index] = '\0';
	return (dst);
}
