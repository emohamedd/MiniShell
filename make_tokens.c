/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haarab <haarab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 20:32:31 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/22 05:48:13 by haarab           ###   ########.fr       */
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

int is_char_in2d(char **str) 
{
    int i = 0;
    int j;
    while (str[i]) 
    {
        j  = 0;
         while (str[i][j]) 
        {
            if ((str[i][j] >= 'a' && str[i][j] <= 'z') || (str[i][j] >= 'A' && str[i][j] <= 'Z'))
            return 1;
           j++; 
        }
        i++;
    }
    return 0;
}


int lenght_of_the_2d(char **p)
{
    if (!p[0])
        return 0;
    int i = 0;
    while(p[i])
    {
        i++;
    }
    return i;
}

char **split(char *s, char *delimiters) 
{
    int max_tokens = strlen(s); // to fix hadi ba9i makanacllokich the right size
        // printf("**********\n");
        // exit(1);
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
        else if ((!in_quotes && strchr(delimiters, end[i]) != NULL) || (!in_quotes && (end[i] == ' ' || end[i] == '\t'))) 
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
char** expand_quotes(char** tokens)
{
    int i = 0;
    int num_quotes = 0;
    
    while (tokens[i]) 
    {
        if (strchr(tokens[i], '\"')) 
        {
            num_quotes++;
        }
        i++;
    }

    char** expanded_tokens = malloc((i + num_quotes + 1) * sizeof(char*));
    if (expanded_tokens == NULL) 
    {
        return NULL;
    }

    int j = 0;
    i = 0;
    while (tokens[i]) 
    {
        char* current_token = tokens[i];
        if (strchr(current_token, '\"')) 
        {
            int token_length = strlen(current_token);
            char* modified_token = malloc(token_length * sizeof(char));
            if (modified_token == NULL) 
            {
                return NULL; 
            }

            int k = 0;
            int l = 0;
            while (l < token_length) 
            {
                if (current_token[l] != '\"') 
                {
                    modified_token[k] = current_token[l];
                    k++;
                }
                l++;
            }
            modified_token[k] = '\0';
            expanded_tokens[j] = modified_token;
            j++;
        } else 
        {
            expanded_tokens[j] = strdup(current_token);
            if (expanded_tokens[j] == NULL) 
            {
                return NULL; 
            }
            j++;
        }
        i++;
    }
    expanded_tokens[j] = NULL;
    return expanded_tokens;
}

char** expand_s_quotes(char** tokens)
{
    int i = 0;
    int num_quotes = 0;
    
    while (tokens[i]) 
    {
        if (strchr(tokens[i], '\'')) 
        {
            num_quotes++;
        }
        i++;
    }

    char** str_s = malloc((i + num_quotes + 1) * sizeof(char*));
    if (str_s == NULL) 
    {
        return NULL;
    }

    int j = 0;
    i = 0;
    while (tokens[i]) 
    {
        char* current_token = tokens[i];
        if (strchr(current_token, '\'')) 
        {
            int token_length = strlen(current_token);
            char* modified_token = malloc(token_length * sizeof(char));
            if (modified_token == NULL) 
            {
                return NULL; 
            }

            int k = 0;
            int l = 0;
            while (l < token_length) 
            {
                if (current_token[l] != '\'') 
                {
                    modified_token[k] = current_token[l];
                    k++;
                }
                l++;
            }
            modified_token[k] = '\0';
            str_s[j] = modified_token;
            j++;
        } else 
        {
            str_s[j] = strdup(current_token);
            if (str_s[j] == NULL) 
            {
                return NULL; 
            }
            j++;
        }
        i++;
    }
    str_s[j] = NULL;
    return str_s;
}


// hna fin kantokinazi
char **make_token(char *s) 
{
    char *special_chars = "<>|";
    char **tokens = split(s, special_chars);
    char **quote = expand_quotes(tokens);
    // char **sgl = expand_s_quotes(quote);
    return red_to_herdoc(quote);
    // return tokens;
}

char	*alloc_s(char const *s, unsigned int start, int len)
{
	char	*stock;
	if (!s || !s[0])
		return (NULL);
	if (start >= ft_strlen(s))
		return ("");
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	stock = ft_strdup(s + start);
	if (!stock)
		return (NULL);
	stock[len] = '\0';
	return (stock);
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
        //     if (inf[i]->content[0] == '\'' && inf[i]->content[strlen(inf[i]->content) - 1] == '\'') 
        // {
        //     inf[i + 1]->content = s[i + 1];
        //         // exit(1);
        //     // printf("HERE inf[i]->content = %s | \n", inf[i + 1]->content);
        // }
        // if(!inf[i]->content[0])
        // {
        //     printf("ERR\n");
        //     pause();
        // }
        // inf[i]->size = lenght_of_the_2d(s);
        // if (inf[i]->content[0] == '\'' && inf[i]->content[strlen(inf[i]->content) - 1] == '\'') 
        // {
        //         // printf("%s\n", "str");//
        //         char *str = ft_strtrim(inf[i]->content, "\'");
        //          char *var ;
        //         var = ft_getenv(str + 1, vars);     
        //             if(!var)
        //                 return 0;
        //             inf[i]->content = ft_strdup(var);

        //             // printf("%s\n", inf[i]->content);
        //             inf[i]->type = "ENV_EXPANDED"; 
        //             inf[i]->lenght = strlen(inf[i]->content);   
        // }
        // printf("*****%s****\n", inf[i + 1]->content);
            int j = 0;
            if (inf[i]->content[0] == '<')   
                inf[i]->type = "RDIN";
            else if (inf[i]->content[0] == '>')
                inf[i]->type = "RDOUT";
            else if (inf[i]->content[0] == '|')
                inf[i]->type = "PIPE";
            else if (inf[i]->content[0] == '\"')
                inf[i]->type = "DBCOTE";
            // while(j < ft_strlen(inf[i]->content))
            // { 
                if (inf[i]->content[0] == '$' && ft_isalpha(inf[i]->content[1]))
                {
                //     int len = ft_strlen(inf[i]->content) - j;
                //    char *expand = alloc_s(inf[i]->content, j + 1, len);
                    char *var = ft_getenv(inf[i]->content + 1, vars);
                        if(!var)
                        {
                            return 0;
                        }
                        inf[i]->content = ft_strdup(var);
                        // printf("%s\n", inf[i]->content);
                        inf[i]->type = "ENV_EXPANDED"; 
                        inf[i]->lenght = strlen(inf[i]->content);
                }
                // j++;
            // }
             if (inf[i]->content[0] == '\'')
                inf[i]->type = "SGCOTE";
            else if (is_char(s[i]))
                inf[i]->type = "STR";
            inf[i]->lenght = strlen(inf[i]->content);
        i++;
    }
    return inf;
}
