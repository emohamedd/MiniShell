/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_single_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 10:58:11 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/30 21:33:48 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

int	count_single_quotes(char **tokens)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (tokens[i])
	{
		if (ft_strchr(tokens[i], '\''))
		{
			count++;
		}
		i++;
	}
	return (count);
}

char	*remove_single_quotes(const char *token)
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
		if (token[l] != '\'')
		{
			modified_token[k] = token[l];
			k++;
		}
		l++;
	}
	modified_token[k] = '\0';
	return (modified_token);
}

char	**expand_s_quotes(char **tokens)
{
	t_sq	sq;

	sq.num_quotes = count_single_quotes(tokens);
	sq.total_tokens = 0;
	sq.i = -1;
	while (tokens[++sq.i])
		sq.total_tokens++;
	sq.expanded_tokens = malloc_(((sq.total_tokens + sq.num_quotes + 1)
				* sizeof(char *)), NULL, 0, NULL);
	if (sq.expanded_tokens == NULL)
		return (NULL);
	sq.i = -1;
	sq.j = 0;
	while (tokens[++sq.i])
	{
		sq.current_token = tokens[sq.i];
		if (ft_strchr(sq.current_token, '\''))
			sq.expanded_tokens[sq.j] = remove_single_quotes(sq.current_token);
		else
			sq.expanded_tokens[sq.j] = ft_strdup(sq.current_token);
		if (sq.expanded_tokens[sq.j] == NULL)
			return (NULL);
		sq.j++;
	}
	return ((sq.expanded_tokens[sq.j] = NULL), sq.expanded_tokens);
}
