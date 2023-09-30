/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_double_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 10:57:41 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/29 13:39:28 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdlib.h>

int count_quotes(char **tokens) {
    int count = 0;
    int i = 0;

    while (tokens[i]) {
        if (ft_strchr(tokens[i], '\"')) {
            count++;
        }
        i++;
    }

    return count;
}

char *remove_quotes(const char *token) 
{
    int token_length = ft_strlen(token);
    // char *modified_token = malloc(token_length * sizeof(char));
	char *modified_token =  malloc_((token_length * sizeof(char)), NULL, 0, NULL);
    if (modified_token == NULL) {
        return NULL;
    }

    int k = 0;
    int l = 0;
    while (l < token_length) {
        if (token[l] != '\"') {
            modified_token[k] = token[l];
            k++;
        }
        l++;
    }

    modified_token[k] = '\0';
    return modified_token;
}

char **expand_quotes(char **tokens) 
{
    int num_quotes = count_quotes(tokens);
    int total_tokens = 0;
    int i = 0;

    while (tokens[i]) 
	{
        total_tokens++;
        i++;
    }

    // char **expanded_tokens = malloc((total_tokens + num_quotes + 1) * sizeof(char *));
	 char **expanded_tokens  = malloc_(((total_tokens + num_quotes + 1) * sizeof(char *)), NULL, 0, NULL);
    if (expanded_tokens == NULL) {
        return NULL;
    }

    int j = 0;
    i = 0;
    while (tokens[i]) {
        char *current_token = tokens[i];
        if (ft_strchr(current_token, '\"')) 
		{
            char *modified_token = remove_quotes(current_token);
            if (modified_token == NULL) {
                return NULL;
            }
            expanded_tokens[j] = modified_token;
            j++;
        } else {
            expanded_tokens[j] = ft_strdup(current_token);
            if (expanded_tokens[j] == NULL) {
                return NULL;
            }
            j++;
        }
        i++;
    }

    expanded_tokens[j] = NULL;
    return expanded_tokens;
}
