/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:31:34 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/08 16:32:38 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// int is_whitespace(char c) 
// {
//     return (c == ' ' || c == '\t');
// }

// int is_a_spchar(char c) 
// {
//     char special_chars[] = "\"\'|<>$";
//     int i = 0;
//     while (special_chars[i]) {
//         if (c == special_chars[i])
//             return 1;
//         i++;
//     }
//     return 0;
// }

// int is_char(char *str) 
// {
//     int i = 0;
//     while (str[i]) 
//     {

//         if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z'))
//             return 1;
//         i++;
//     }
//     return 0;
// }

// int size_ar(t_info **arr) 
// {
//     int i = 0;
//     while (arr[i] != NULL) {
//         i++;
//     }
//     return i;
// }

// t_info **appand(t_info **token, t_info *info, int *token_size) 
// {
//     // (*token_size)++;
//    t_info **new_token = malloc((*token_size + 1) * sizeof(t_info *));

//     int i = 0;
//     while (i < *token_size) 
//     {
//         new_token[i] = token[i];
//         i++;
//     }
//     new_token[*token_size] = NULL;

    
//     token = new_token;
//     (*token_size)++;


//     if (token == NULL) 
//     {
//         printf("Eroor\n");
//         exit(1);
//     }
//     token[*token_size - 1] = info;
//     token[*token_size] = NULL;
//     return token;
// }

// t_info **ft_split(char *s) 
// {
//     int token_size = 0;
//     t_info **token = malloc((token_size + 1) * sizeof(t_info *));
//     if (token == NULL) 
//     {
//        printf("Eroor\n");
//         exit(1);
//     }
//     token[token_size] = NULL;
    
//     int i = 0;
//     while (s[i]) 
//     {
//         while (s[i] && (is_whitespace(s[i])))
//             i++;
//         if (s[i]) 
//         {
//             int start = i;
//             while (s[i] && (!is_whitespace(s[i])))
//                 i++;
//             int token_length = i - start;

//             t_info *inf = malloc(sizeof(t_info));
//             if (inf == NULL) 
//             {
//                 printf("Eroor\n");
//                 exit(1);
//             }

//             inf->content = malloc((token_length + 1) * sizeof(char));
//             if (inf->content == NULL) 
//             {
//                 printf("Eroor\n");
//                 exit(1);
//             }

//             int j = 0;
//             while (start < i) 
//             {
//                 inf->content[j] = s[start];
//                 if (inf->content[j] == '<')
//                     inf->type = "RDIN";
//                 else if (inf->content[j] == '>')
//                     inf->type = "RDOUT";
//                 else if (inf->content[j] == '|')
//                     inf->type = "PIPE";
//                 else if (inf->content[j] == '\"')
//                     inf->type = "DBCOTE";
//                 else if (inf->content[j] == '$')
//                     inf->type = "ENV";
//                 else if (inf->content[j] == '\'')
//                     inf->type = "SGCOTE";
//                 else if (!is_a_spchar(s[i]) && !is_char(s))
//                     inf->type = "AUT";
//                 else if (is_char(s))
//                     inf->type = "STR";
//                 inf->lenght = strlen(inf->content);
//                 j++;
//                 start++;
//             }
//             inf->content[j] = '\0';

//             token = appand(token, inf, &token_size);
//         }
//     }

//     return token;
// }

// t_info **appand(t_info **token, t_info *info)
// {
//     int size = size_ar(token);
//     token = malloc( (size + 2) * sizeof(t_info *));


//     token[size] = malloc(sizeof(t_info));
//     token[size]->content = strdup(info->content); 
//     // token[size]->type = NULL; 
//     // token[size]->length = info->length;
//     token[size + 1] = NULL;

//     return token;
// }
// t_info **ft_split(char *s)
// {
//     t_info *inf = NULL;
//     int end = 0;
//     int start = 0;
//     int i = 0;
//     t_info **token = NULL;

//     while (s[i])
//     {
//         start = i;
//         if (is_whitespace(s[i]) || is_a_spchar(s[i]))
//             end = i;
//         int token_length = end - start;

//         token = malloc((i + 2) * sizeof(t_info *));
//         token[i] = malloc(sizeof(t_info));
//         token[i]->content = (char *)malloc(token_length + 1);
//         strncpy(token[i]->content, &s[start], token_length);
//         token[i]->content[token_length] = '\0';
//         // token[i]->type = NULL;
//         // token[i]->lenght = token_length;
//         token[i + 1] = NULL;

//         token = appand(token, inf);
//         i++;
//     }

//     return token;
// }
