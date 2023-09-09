/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 13:10:25 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/09 11:01:39 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int main()
{
    // t_info *info = NULL;
    char *input;
    char **str;   
    t_info **tokens = NULL; 
    while(1)
    {
        int i = 0;
        // display_prompt();
        input = read_input();
        if (input == NULL)
            return (1);
            str =  make_token(input);
        if(str)
        {
        tokens = allocat_token(str);
        if(!tokens)
            continue;
        printf("+%s--------------------------------------------------------------+|%s\n", PURPLE, RESET);
        printf("|     %sTOKEN         |       LENGHT     |     %sTYPE    %s\n", GREEN, GREEN, GREEN);
        printf("+%s--------------------------------------------------------------+|%s\n", PURPLE, RESET);

        while (str[i]) 
        {
            printf("    %s%s%s           |         %d%s        |      %s\n", YELLOW, tokens[i]->content, YELLOW, tokens[i]->lenght, YELLOW, tokens[i]->type);
            printf("+%s--------------------------------------------------------------+|%s\n", PURPLE, RESET);
            i++;
        }     
        }
    }
    return 0;
}

//lez beda bda kayban hadchi db baybqaw dok les cas dyal quote wst mnha expand dak tkhrbiq kaymrd mohim beda bdat katban qadia
//yalah a hamza byn lia tanta ach endk
// good luck mate :)