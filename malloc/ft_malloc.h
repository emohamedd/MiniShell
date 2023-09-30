/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 17:20:01 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/28 07:43:11 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

enum e_a_types {
	ALLOC,
	FREE,
	FREE_ALL,
	T_SIZE,
};

struct s_address
{
	void					*ptr;
	unsigned int			size;
	bool					dealloc;
	struct s_address		*next;
	struct s_address		*prev;
};
typedef struct s_address	t_address;

void		*malloc_(unsigned int size, void	*free_ptr,
				int type, uint32_t *t_size);
t_address	*create_node(void *ptr, unsigned int size);
void		add_node_back(t_address **head, t_address *node);
void		destroy_node(t_address *node);
void		print_string(char *string);
void		print_number(unsigned int number);
void		print_str_with_int(char *string, unsigned int n);
#endif