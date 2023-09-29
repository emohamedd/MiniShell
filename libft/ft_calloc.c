/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haarab <haarab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 12:38:12 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/29 15:24:43 by haarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	sizee;
	void	*p;

	p = NULL;
	sizee = count * size;
	// p = malloc(sizee);
	p = malloc_(sizee, NULL, 0, NULL);
	if (!p)
		return (NULL);
	ft_bzero(p, sizee);
	return (p);
}
