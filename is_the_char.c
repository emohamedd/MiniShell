/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_the_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:52:36 by emmd              #+#    #+#             */
/*   Updated: 2023/09/05 16:49:36 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int is_whitespace(char c)
// {
//     if(c == ' ' || c == '\t')
//         return 1;
//     return 0;
// }

// int is_special_char(char c)
// {
//     char special_chars[] = "|><;&$";
//     int i = 0;
//     while(special_chars[i])
//     {
//         if (c == special_chars[i])
//             return 1;
//     i++;
//     }
//     return 0;
// }

// t_info **ft_split(char *s)
// {
//     t_info *inf = NULL;

//     inf->content = 0;
//     inf->type = 0;
//     int max_tokens = 20; //hadi ha temporaire ela wdit allocation wsf mn b3d hanhsb exact tokens li kaynin w hanetihom exact allocation 
//    t_info **tokens = malloc(max_tokens * sizeof(t_info *));
//     if(!tokens)
//     {
//         printf("Memory allocation failed\n");
//         exit(1);
//     }
    
//     int num_tokens = 0;
//     int i = 0;
//     while(s[i])
//     {
//         //hna kanskipi withspaces
//         while(s[i] && is_whitespace(s[i]))
//         {
//             i++;
//         }
//     if (s[i])
//         {
//             int start = i;
            
//             while(s[i] && (!is_whitespace(s[i])  || is_special_char(s[i])))
//             {
//                 //hna kan9lb ela end dyal token
//             // printf("%d\n", i);
//                 i++;
//             }
//             // exit(1);
            
//             int end = i;
//             if (num_tokens >= max_tokens)
//             {
//                 printf("Max number of tokens reached\n");
//                 exit(1);
//             }
//             //db hancopiyi tokens l array
//             int token_lenght = end - start;
//             inf->lenght = token_lenght;
//             tokens[num_tokens] =  malloc(token_lenght + 1); // +1 dyal end of array
//             inf->content = malloc(token_lenght + 1);
//             if (!tokens[num_tokens])
//             {
//                 printf("Memory allocation failed\n");
//                 exit(1);
//             }
//             // db hancopi char wahd b wahd
//             int j = 0;
//             while (start < end)
//             {
//                 // tokens[num_tokens][j] = s[start];
            
//                inf->content[j] = s[start];
//                 j++;
//                 start++;
//             }
//             inf->content[j] = '\0';
//             tokens[num_tokens] = inf;
//             num_tokens++; 
//         }
//     }
//     tokens[num_tokens] = NULL;
//     return tokens;
// }