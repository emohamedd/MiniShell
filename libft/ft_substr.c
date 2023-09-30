/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 10:39:39 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/30 05:11:49 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_substr(char const *s, int start, int len)
{
	char	*stock;

	if (!s || !s[0])
		return (NULL);
	if (start >= ft_strlen(s))
		return ("");
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	stock = ft_strdup(s + start);
	if (!stock)
		return (NULL);
	stock[len] = '\0';
	return (stock);
}
