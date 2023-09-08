/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 08:46:46 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/08 10:01:52 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.c"  


#include <string.h>
#include <stdio.h>
    
void make_token(char *s, int *quotestate) 
{
    int i = 0;
    int insg = 0;
    int indb = 0;

    while (s[i]) 
    {
        if (s[i] == '\'' && !indb) 
        {
            
            s[i] = 16;
            insg = !insg;
        } 
        else if (s[i] == '"' && !insg) 
        {  
                
            s[i] = 16;
            indb = !indb;
        }
        i++;
    }
    if (insg || indb) 
        *quotestate = 1;
     else 
        *quotestate = 0;
}




int main() 
{
    char input[] = "echo '\"   '   '  \"' > \"file.txt'\" ";
    int quoteState = 0; 

    make_token(input, &quoteState);

    printf("%s\n", input);
    printf("Quote %d\n", quoteState);

    return 0;
}

