/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 17:01:08 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/14 17:08:02 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void syn_err(char **str)
{
    int i = 0;
    int j = 0;
    while(str[i])
    {
        while(str[i][j])
        {
            if((str[i][0] == '>' || str[i][0] == '<' || str[i][j] == '|'))
                printf("syntax error near unexpected token\n");
            j++;
        }
        i++;
    }
}