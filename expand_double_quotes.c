/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_double_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 10:57:41 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/29 11:03:50 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**expand_quotes(char **tokens)
{
	int		i;
	int		num_quotes;
	char	**expanded_tokens;
	int		j;
	char	*current_token;
	int		token_length;
	char	*modified_token;
	int		k;
	int		l;

	i = 0;
	num_quotes = 0;
	while (tokens[i])
	{
		if (ft_strchr(tokens[i], '\"'))
		{
			num_quotes++;
		}
		i++;
	}
	// expanded_tokens = malloc((i + num_quotes + 1) * sizeof(char *));
	expanded_tokens = malloc_(((i + num_quotes + 1) * sizeof(char *)), NULL, 0, NULL);
	if (expanded_tokens == NULL)
	{
		return (NULL);
	}
	j = 0;
	i = 0;
	while (tokens[i])
	{
		current_token = tokens[i];
		if (ft_strchr(current_token, '\"'))
		{
			token_length = ft_strlen(current_token);
			// modified_token = malloc(token_length * sizeof(char));
			modified_token = malloc_((token_length * sizeof(char)), NULL, 0, NULL);
			if (modified_token == NULL)
			{
				return (NULL);
			}
			k = 0;
			l = 0;
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
		}
		else
		{
			expanded_tokens[j] = ft_strdup(current_token);
			if (expanded_tokens[j] == NULL)
			{
				return (NULL);
			}
			j++;
		}
		i++;
	}
	expanded_tokens[j] = NULL;
	return (expanded_tokens);
}
