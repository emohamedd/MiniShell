/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 21:17:07 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/28 21:20:11 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_2d_array(char **array)
{
    if (array)
    {
        for (int i = 0; array[i]; i++)
        {
            free(array[i]);
        }
        free(array);
    }
}

void free_tokens(t_info **tokens)
{
    if (tokens)
    {
        for (int i = 0; tokens[i]; i++)
        {
            free(tokens[i]->content);
            free(tokens[i]);
        }
        free(tokens);
    }
}
