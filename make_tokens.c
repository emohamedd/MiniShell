/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 08:46:46 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/08 13:18:17 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"  

char **make_token(char *s, int *quotestate) 
{
	char **input;
    int i = 0;
    int insg = 0;
    int indb = 0;

    while (s[i]) 
    {
        if ((s[i] == '\'' && !indb))
        {
            s[i] = 16;
            insg = !insg;
        } 
        else if ((s[i] == '"' && !insg) )
        {  
                
            s[i] = 16;
            indb = !indb;
        }
        else if (!insg && !indb && s[i] == ' ') 
            s[i] = 16;
        i++;
    }
    if (insg || indb) 
        *quotestate = 1;
     else 
        *quotestate = 0;
	input = ft_split_token(s, 16);
	return input;
}

