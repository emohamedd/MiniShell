/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:31:34 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/06 10:45:52 by emohamed         ###   ########.fr       */
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

    int i = 0;
 
    token = malloc((size_ar(token) + 1) + 1 * sizeof(t_info));
    info->content = strdup(token[i]->content);
    // info->type = NULL;
    // info->lenght = strlen(token);
    while(i < size_ar(token))
    {
        token[i] = info;
        i++;
    }
    token[i] = info;
    token[i + 1] = 0;
    return token;
}

t_info **ft_split(char *s)
{
    t_info *inf = NULL;
    int end = 0;
    int start = 0;
    int i = 0;
    t_info **token = NULL;

    while(s[i])
    {
        start = i;
        if (is_whitespace(s[i]) || is_a_spchar(s[i]))
            end = i;
        int token_lenght = end - start;

       token = malloc(token_lenght + 1);

        int j = 0;
        int v = 0;
       while(start < end)
       {
            token[v]->content[j] = s[start];
            j++;
            start++;
       }
       token[j] = 0;
      token = appand(token, inf);

      i++;
    }
       return token;
}
