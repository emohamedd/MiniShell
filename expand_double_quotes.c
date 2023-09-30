/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_double_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 10:57:41 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/30 15:29:24 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

int	count_quotes(char **tokens)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (tokens[i])
	{
		if (ft_strchr(tokens[i], '\"'))
		{
			count++;
		}
		i++;
	}
	return (count);
}

char	*remove_quotes(char *token)
{
	int		token_length;
	char	*modified_token;
	int		k;
	int		l;

	token_length = ft_strlen(token);
	modified_token = malloc_((token_length * sizeof(char)), NULL, 0, NULL);
	if (modified_token == NULL)
	{
		return (NULL);
	}
	k = 0;
	l = 0;
	while (l < token_length)
	{
		if (token[l] != '\"')
		{
			modified_token[k] = token[l];
			k++;
		}
		l++;
	}
	modified_token[k] = '\0';
	return (modified_token);
}

char	**expand_quotes(char **tokens)
{
	t_dq	dq;

	dq.num_quotes = count_quotes(tokens);
	dq.total_tokens = 0;
	dq.i = 0;
	while (tokens[dq.i])
	{
		dq.total_tokens++;
		dq.i++;
	}
	dq.expanded_tokens = malloc_(((dq.total_tokens + dq.num_quotes + 1)
				* sizeof(char *)), NULL, 0, NULL);
	if (dq.expanded_tokens == NULL)
	{
		return (NULL);
	}
	dq.j = 0;
	dq.i = 0;
	while (tokens[dq.i])
	{
		dq.current_token = tokens[dq.i];
		if (ft_strchr(dq.current_token, '\"'))
		{
			dq.modified_token = remove_quotes(dq.current_token);
			if (dq.modified_token == NULL)
			{
				return (NULL);
			}
			dq.expanded_tokens[dq.j] = dq.modified_token;
			dq.j++;
		}
		else
		{
			dq.expanded_tokens[dq.j] = ft_strdup(dq.current_token);
			if (dq.expanded_tokens[dq.j] == NULL)
			{
				return (NULL);
			}
			dq.j++;
		}
		dq.i++;
	}
	dq.expanded_tokens[dq.j] = NULL;
	return (dq.expanded_tokens);
}
