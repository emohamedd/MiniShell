/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 17:20:06 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/30 02:46:32 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	destroy_node(t_address *node)
{
	if (node == NULL)
		return ;
	if (node->ptr)
	{
		free (node->ptr);
		node->dealloc = 1;
		node->ptr = NULL;
		node->size = 0;
	}
	free(node);
	node = NULL;
}

t_address	*create_node(void *ptr, unsigned int size)
{
	t_address	*node;

	node = malloc(sizeof(t_address));
	if (node == NULL)
		return (NULL);
	node->size = size;
	node->dealloc = 0;
	node->prev = NULL;
	node->next = NULL;
	node->ptr = ptr;
	return (node);
}

void	add_node_back(t_address **head, t_address *node)
{
	t_address	*temp;

	temp = *head;
	if (!*head)
	{
		*head = node;
		return ;
	}
	else if (temp)
	{
		while (temp->next)
			temp = temp->next;
	}
	temp->next = node;
	node->prev = temp;
}
