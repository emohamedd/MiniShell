/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 08:46:46 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/08 16:30:01 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"  

int is_char(char *str) 
{
    int i = 0;
    while (str[i]) 
    {

        if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z'))
            return 1;
        i++;
    }
    return 0;
}

int lenght_of_the_2d(char **p)
{
    int i = 0;
    while(p[i])
    {
        i++;
    }
    return i;
}

char **make_token(char *s) 
{
    int quotestate = 0;
    char  **token = NULL;
    int i = 0;
    int insg = 0;
    int indb = 0;

    while (s[i]) 
    {
            if ((s[i] == '\'' && !indb))
            {
                s[i] = 16;
                insg = !insg;
            } 
            else if ((s[i] == '"' && !insg) )
            {  
                    
                s[i] = 16;
                indb = !indb;
            }
            else if (!insg && !indb && s[i] == ' ') 
                s[i] = 16;
            i++;
            if (insg || indb) 
                quotestate = 1;
            else 
                quotestate = 0;
            
        token = ft_split_token(s, 16);
    }
    return token;
}

t_info **allocat_token(char **s)
{
    int  i = 0;
     t_info **inf = malloc(sizeof(t_info*) * lenght_of_the_2d(s)+1);
         if (!inf) 
            {
                printf("Err\n");
                exit(1);
            }
    while(s[i])
    {
        inf[i] = malloc(sizeof(t_info));
        inf[i]->content = s[i];
        if (inf[i]->content[0] == '<')
            inf[i]->type = "RDIN";
        else if (inf[i]->content[0] == '>')
            inf[i]->type = "RDOUT";
        else if (inf[i]->content[0] == '|')
            inf[i]->type = "PIPE";
        else if (inf[i]->content[0] == '\"')
            inf[i]->type = "DBCOTE";
        else if (inf[i]->content[0] == '$')
            inf[i]->type = "ENV";
        else if (inf[i]->content[0] == '\'')
            inf[i]->type = "SGCOTE";
        else if (is_char(s[i]))
            inf[i]->type = "STR";
        inf[i]->lenght = strlen(inf[i]->content);
        i++;
    }
    return inf;
}

// #include <stdio.h>

// int main()
// {
//     int i = 0;
//     char s[] = "echo amine > \"file txt\"";
//     char **str = make_token(s);
//     while(str[i])
//     {
//         printf("----> %s\n", str[i]);
//         i++;
//     }
// }