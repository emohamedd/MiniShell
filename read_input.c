/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haarab <haarab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 17:40:23 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/08 13:03:40 by haarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *read_input()
{
	char *str = "aminoarab-> ";
    char *in = readline(str);
    if (in)
        add_history(in);
    return in;
}