/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 12:38:12 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/30 02:48:12 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	sizee;
	void	*p;

	p = NULL;
	sizee = count * size;
	p = malloc_(sizee, NULL, 0, NULL);
	if (!p)
		return (NULL);
	ft_bzero(p, sizee);
	return (p);
}
