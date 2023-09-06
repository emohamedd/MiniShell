/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:31:34 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/06 13:01:46 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_whitespace(char c)
{
    if (c == ' ' || c == '\t')
        return 1;
    return 0;
}

int is_a_spchar(char c)
{
    char special_chars[] = "\" \'|<>$";
    int i = 0;
    while(special_chars[i])
    {
        if (c == special_chars[i])
            return 1;
        i++;
    }
    return 0;
}
int is_char(char *str)
{
    int i = 0;
    while(str[i])
    {
        if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z'))
            return 1;
        i++;
    }
    return 0;
}

int size_ar(t_info **arr)
{
    int i = 0;
    while (arr[i])
    {
        i++;
    }
    return i;
}



t_info **appand(t_info **token, t_info *info)
{
    t_info **new;
    int i = 0;
 
    new = malloc((size_ar(token) + 2) * sizeof(t_info));
    // info->content = strdup(token[i]->content);
    // info->type = NULL;
    // info->lenght = strlen(token);
    while(i < size_ar(token))
    {
        new[i] = token[i];
        i++;
    }
    new[i] = info;
    new[i + 1] = 0;
    return new;
}

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

t_info **ft_split(char *s)
{
    t_info *inf = NULL;
    int end = 0;
    int start = 0;
    int i = 0;
    t_info **token = NULL;

    while(s[i])
    {
        while(s[i])
        {
        start = i;
        if (is_whitespace(s[i]) || is_a_spchar(s[i]))
            {
                end = i;
                break;
            }
            i++;
        }
        i = start;
        int token_lenght = end - start;
       inf = malloc(sizeof(t_info));
       inf->content  =  malloc(token_lenght * sizeof(t_info));
        int j = 0;
        // int v = 0;

       while(start < end)
       {
            inf->content[j] = s[start];
            j++;
            start++;
       }
       token[j] = 0;
      token = appand(token, inf);

      i++;
    }
       return token;
}
