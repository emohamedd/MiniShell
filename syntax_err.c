/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 17:01:08 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/23 15:19:47 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// int  is_special_char(char c) 
// {
//     char special_chars[] = "><|&;";
//     int i = 0;
//     while(special_chars[i])
//     {
//         if (c == special_chars[i]) 
//         {
//             return 1;
//         }
//         i++;
//     }
//     return 0;
// }

// void syn_err(char **str, t_vars *vars) 
// {
    
//     int i = 0;
//     while (str[i]) 
//     {
//         int j = 0;
//         while (str[i][j]) 
//         {
//             if (is_special_char(str[i][j])) 
//             {
//                 printf("minishell: syntax error\n");
//                 vars->exit_status = 2;
//             } 
//             else if (str[i][j] == '\'' || str[i][j] == '\"') 
//             {
//                 char quote = str[i][j];
//                 int k = j + 1;
//                 while (str[i][k] && str[i][k] != quote) 
//                 {
//                     k++;
//                 }
//                 if (!str[i][k]) 
//                 {
//                      printf("minishell: syntax error\n");
//                     vars->exit_status = 2;
//                 }
//                 j = k;
//             }
//             j++;
//         }
//         i++;
//     }
// }
void syn_err(char **str, t_vars *vars)
{

    int i = 0;
    int j = 0;
    while(str[i])
    {
        while(str[i][j])
        {
            if((str[i][0] == '>' || str[i][j] == '|'))
            {
                printf("minishell: syntax error\n");
                vars->exit_status = 2;
            }
            j++;
        }
        i++;
    }
}