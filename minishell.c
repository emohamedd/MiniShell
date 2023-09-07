/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 13:10:25 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/07 12:38:59 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int main()
{
    // t_info *info = NULL;
    char *input;
    t_info **str;    
    while(1)
    {
        int i = 0;
        // display_prompt();
        input = read_input();

        str =  ft_split(input);
 
    printf("+%s----------------------------------------------------------+|%s\n", PURPLE, RESET);
    printf("|     %sTOKEN         |       LENGHT     |     %sTYPE    %s\n", GREEN, GREEN, GREEN);
    printf("+%s----------------------------------------------------------+|%s\n", PURPLE, RESET);

    while (str[i]) 
    {
        printf("|    %s%s%s           |         %d%s        |      %s\n", YELLOW, str[i]->content, YELLOW, str[i]->lenght, YELLOW, str[i]->type);
        printf("+%s----------------------------------------------------------+|%s\n", PURPLE, RESET);
        i++;
    }
    }
    return 0;
}

//lez beda bda kayban hadchi db baybqaw dok les cas dyal quote wst mnha expand dak tkhrbiq kaymrd mohim beda bdat katban qadia
//yalah a hamza byn lia tanta ach endk
// good luck mate :)