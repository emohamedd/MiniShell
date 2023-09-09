/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 17:40:23 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/09 16:43:03 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *read_input()
{
    char *in =  readline("amineoaarab$ ");
    if (in)
        add_history(in);
    return in;
}
