/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 13:10:25 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/06 12:20:50 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int main()
{
    t_info *info = NULL;
    char *input;
    t_info **str;    
    while(1)
    {
        int i = 0;
        // display_prompt();
        input = read_input();

        str =  ft_split(input);
       
        
    // while(str[i])
    // {
    //     printf("%s  ", str[i]);
    //     i++;
    // }
    //  printf("+%s------------------------+%s\n", PURPLE, RESET);
    // printf("|     %sToken%s          |\n", GREEN, RESET);
    // printf("+%s------------------------+%s\n", PURPLE, RESET);

    // while (str[i]) {
    //     printf("| %s%-20s%s |\n", YELLOW, str[i], RESET);
    //     printf("+%s------------------------+%s\n", PURPLE, RESET);
    //     i++;
    // }
    while(str[i])
    {
        printf("Content : %s", info->content);
        i++;
    }
    }
    return 0;
}

//lez beda bda kayban hadchi db baybqaw dok les cas dyal quote wst mnha expand dak tkhrbiq kaymrd mohim beda bdat katban qadia
//yalah a hamza byn lia tanta ach endk
// good luck mate :)