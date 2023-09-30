/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   giga_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 10:56:43 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/30 02:37:53 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split(char *s, char *delimiters)
{
	int		max_tokens;
	char	**tokens;
	int		token_count;
	char	*start;
	char	*end;
	int		in_quotes;
	char	quote_char;
	int		escaped;
	int		i;
	char	**new_tokens;

	max_tokens = ft_strlen(s) + 1;
	tokens = malloc_((max_tokens * sizeof(char *)), NULL, 0, NULL);
	if (!tokens)
	{
		printf("allocation err\n");
		exit(1);
	}
	token_count = 0;
	start = s;
	end = s;
	in_quotes = 0;
	quote_char = '\0';
	escaped = 0;
	i = 0;
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
		else if ((!in_quotes && ft_strchr(delimiters, end[i]) != NULL)
			|| (!in_quotes && (end[i] == ' ' || end[i] == '\t')))
		{
			if (start != end)
			{
				if (token_count >= max_tokens)
				{
					max_tokens *= 2;
					new_tokens = malloc_((max_tokens * sizeof(char *)), NULL, 0, NULL);
					if (!new_tokens)
					{
						printf("allocation err\n");
						exit(1);
					}
					i = 0;
					while (i < token_count)
					{
						new_tokens[i] = tokens[i];
						i++;
					}
					tokens = new_tokens;
				}
				tokens[token_count] = malloc_(((end - start + 1) * sizeof(char)), NULL, 0, NULL);
				if (!tokens[token_count])
				{
					printf("allocation err\n");
					exit(1);
				}
				strncpy(tokens[token_count], start, end - start);
				tokens[token_count][end - start] = '\0';
				token_count++;
			}
			if (ft_strchr(delimiters, end[i]) != NULL)
			{
				if (token_count >= max_tokens)
				{
					max_tokens *= 2;
					new_tokens = malloc_((max_tokens * sizeof(char *)), NULL, 0, NULL);
					if (!new_tokens)
					{
						printf("allocation err\n");
						exit(1);
					}
					i = 0;
					while (i < token_count)
					{
						new_tokens[i] = tokens[i];
						i++;
					}
					tokens = new_tokens;
				}
				tokens[token_count] = malloc_((2 * sizeof(char)), NULL, 0, NULL);
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
			new_tokens = malloc_((max_tokens * sizeof(char *)), NULL, 0, NULL);
			if (!new_tokens)
			{
				printf("allocation err\n");
				exit(1);
			}
			i = 0;
			while (i < token_count)
			{
				new_tokens[i] = tokens[i];
				i++;
			}
			tokens = new_tokens;
		}
		tokens[token_count] = malloc_(((end - start + 1) * sizeof(char)), NULL, 0, NULL);
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
	return (tokens);
}
