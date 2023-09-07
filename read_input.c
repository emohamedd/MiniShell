/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 17:40:23 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/07 11:23:18 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *read_input()
{
    char *in =  readline("\x1B[33mamineoaarab\x1B[32m$\x1B[0m ");
    if (in)
        add_history(in);
    return in;
}