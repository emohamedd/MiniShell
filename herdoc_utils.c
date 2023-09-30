/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 15:54:53 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/30 17:37:35 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strcat(char *destination, const char *source)
{
	char	*dest_ptr;

	dest_ptr = destination;
	while (*dest_ptr)
	{
		dest_ptr++;
	}
	while (*source)
	{
		*dest_ptr = *source;
		dest_ptr++;
		source++;
	}
	*dest_ptr = '\0';
	return (destination);
}

char	*ft_strcpy(char *destination, const char *source)
{
	char	*dest_ptr;

	dest_ptr = destination;
	while (*source)
	{
		*dest_ptr = *source;
		dest_ptr++;
		source++;
	}
	*dest_ptr = '\0';
	return (destination);
}

char	*ft_strncpy(char *destination, char *source, int n)
{
	char	*dest_ptr;
	int		i;

	i = 0;
	dest_ptr = destination;
	while (i < n && *source)
	{
		*dest_ptr = *source;
		dest_ptr++;
		source++;
		i++;
	}
	while (i < n)
	{
		*dest_ptr = '\0';
		dest_ptr++;
		i++;
	}
	return (destination);
}
