/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haarab <haarab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 10:08:03 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/23 01:19:06 by haarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (ft_strlen(needle) == 0)
		return ((char *)haystack);
	if (ft_strlen(haystack) == 0 || len == 0)
		return (NULL);
	if ((!needle && !haystack))
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		if (haystack[i] == needle[j] && ft_strncmp(haystack + i, needle,
				ft_strlen(needle)) == 0 && (ft_strlen(needle) + i) <= len)
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}
