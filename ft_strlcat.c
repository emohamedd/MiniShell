/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 13:28:33 by emohamed          #+#    #+#             */
/*   Updated: 2023/07/30 14:27:41 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlcat(char *dst, char *src, size_t dstsize)
{
	size_t	i;
	size_t	dlen;
	size_t	slen;
	size_t	size;

	i = 0;
	dlen = ft_strlen(dst);
	slen = ft_strlen(src);
	if (dstsize == 0 || dlen > dstsize)
		return (dstsize + slen);
	size = dstsize - dlen - 1;
	while (i < size)
	{
		dst[dlen + i] = src[i];
		i++;
	}
	dst[dlen + i] = '\0';
	return (dlen + slen);
}
