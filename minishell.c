/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmd <emmd@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 13:10:25 by emohamed          #+#    #+#             */
/*   Updated: 2023/08/21 15:28:37 by emmd             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int main()
{
    char *input;
    char **str;    
    while(1)
    {
        int i = 0;
        display_prompt();
        input = read_input();
        str = ft_split(input);
        
    while (str[i])
    {
        printf("___________\n");
        printf("\n*   %s%s\n", str[i], "  *");
        printf("___________\n");
        i++;   
    }

    }
    return 0;
}
