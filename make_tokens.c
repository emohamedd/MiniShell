/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 08:46:46 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/11 09:02:44 by emohamed         ###   ########.fr       */
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

char **split(char *s, const char *delimiters) 
{
    t_info *inf;

    int max_tokens = inf->size; // to fix hadi ba9i makanacllokich the right size
    char **tokens = (char **)malloc(max_tokens * sizeof(char *));
    if (!tokens) 
    {
       printf("allocation err\n");
        exit(1);
    }

    int token_count = 0;
    char *start = s;
    char *end = s;
    int in_quotes = 0;
    char quote_char = '\0';
    int escaped = 0;
    int i = 0;

    while (end[i]) 
    {
        if (end[i] == '\'' || end[i] == '\"') 
        {
            if (in_quotes && end[i] == quote_char) 
            {
                in_quotes = 0;
                quote_char = '\0';
            } 
            else if (!in_quotes) 
            {
                in_quotes = 1;
                quote_char = end[i];
            }
            escaped = 0;
        } 
        else if (end[i] == '\\') 
        {
            if (in_quotes) 
            {
                escaped = !escaped;
            }
        } 
        else if (!in_quotes && strchr(delimiters, end[i]) != NULL) 
        {
            if (start != end) 
            {
                if (token_count >= max_tokens) 
                {
                    max_tokens *= 2;
                    char **new_tokens = (char **)malloc(max_tokens * sizeof(char *));
                    if (!new_tokens) 
                    {
                       printf("allocation err\n");
                        exit(1);
                    }
                    int i = 0;
                    while (i < token_count) 
                    {
                        new_tokens[i] = tokens[i];
                        i++;
                    }
                    free(tokens);
                    tokens = new_tokens;
                }
                tokens[token_count] = (char *)malloc((end - start + 1) * sizeof(char));
                if (!tokens[token_count]) 
                {
                   printf("allocation err\n");
                    exit(1);
                }
                strncpy(tokens[token_count], start, end - start);
                tokens[token_count][end - start] = '\0';
                token_count++;
            }
            if (strchr(delimiters, end[i]) != NULL) 
            {
                if (token_count >= max_tokens) 
                {
                    max_tokens *= 2;
                    char **new_tokens = (char **)malloc(max_tokens * sizeof(char *));
                    if (!new_tokens) 
                    {
                       printf("allocation err\n");
                        exit(1);
                    }
                    int i = 0;
                    while (i < token_count) 
                    {
                        new_tokens[i] = tokens[i];
                        i++;
                    }
                    free(tokens);
                    tokens = new_tokens;
                }
                tokens[token_count] = (char *)malloc(2 * sizeof(char));
                if (!tokens[token_count]) 
                {
                   printf("allocation err\n");
                    exit(1);
                }
                tokens[token_count][0] = end[i];
                tokens[token_count][1] = '\0';
                token_count++;
            }
            start = end + 1;
        } 
        else if (escaped) 
        {
            escaped = 0;
        }
        end++;
    }

    if (start != end) 
    {
        if (token_count >= max_tokens) 
        {
            max_tokens *= 2;
            char **new_tokens = (char **)malloc(max_tokens * sizeof(char *));
            if (!new_tokens) 
            {
               printf("allocation err\n");
                exit(1);
            }
            int i = 0;
            while (i < token_count) 
            {
                new_tokens[i] = tokens[i];
                i++;
            }
            free(tokens);
            tokens = new_tokens;
        }
        tokens[token_count] = (char *)malloc((end - start + 1) * sizeof(char));
        if (!tokens[token_count]) 
        {
           printf("allocation err\n");
            exit(1);
        }
        strncpy(tokens[token_count], start, end - start);
        tokens[token_count][end - start] = '\0';
        token_count++;
    }

    tokens[token_count] = NULL;
    return tokens;
}

// hna kan expandi quotes
char **expand_quotes(char **tokens) 
{
    int i = 0;
    while (tokens[i] != NULL) 
    {
        if (tokens[i][0] == '\"' && tokens[i][strlen(tokens[i]) - 1] == '\"') 
        {
            memmove(tokens[i], tokens[i] + 1, strlen(tokens[i]) - 2);
            tokens[i][strlen(tokens[i]) - 2] = '\0';
        }
        i++;
    }
    return tokens;
}

// hna fin kantokinazi
char **make_token(char *s) 
{
    const char *special_chars = "<>|";
    char **tokens = split(s, special_chars);
    tokens = expand_quotes(tokens);

    return tokens;
}

t_info **allocat_token(char **s,  t_vars *vars)
{
    int  i = 0;
   
     t_info **inf = malloc(sizeof(t_info*) * (lenght_of_the_2d(s)+1));
         if (!inf) 
            
            {
                printf("Err\n");
                exit(1);
            }
    while(s[i])
    
    {
        inf[i] = malloc(sizeof(t_info));
        inf[i]->content = s[i];
        inf[i]->size = lenght_of_the_2d(s);
            if (inf[i]->content[0] == '<')
                inf[i]->type = "RDIN";
            else if (inf[i]->content[0] == '>')
                inf[i]->type = "RDOUT";
            else if (inf[i]->content[0] == '|')
                inf[i]->type = "PIPE";
            else if (inf[i]->content[0] == '\"')
                inf[i]->type = "DBCOTE";
            else if (inf[i]->content[0] == '$')
            
            {
                char *var = ft_getenv(inf[i]->content + 1, vars);     
                    if(!var)
                        return 0;
                    inf[i]->content = ft_strdup(var);
                    // printf("%s\n", inf[i]->content);
                    inf[i]->type = "ENV_EXPANDED"; 
                    inf[i]->lenght = strlen(inf[i]->content);
            }
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

