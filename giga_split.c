/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   giga_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 10:56:43 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/30 16:01:27 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split(char *s, char *delimiters)
{
	t_sp	sp;

	sp.max_tokens = ft_strlen(s) + 1;
	sp.tokens = malloc_((sp.max_tokens * sizeof(char *)), NULL, 0, NULL);
	if (!sp.tokens)
	{
		printf("allocation err\n");
		exit(1);
	}
	sp.token_count = 0;
	sp.start = s;
	sp.end = s;
	sp.in_quotes = 0;
	sp.quote_char = '\0';
	sp.escaped = 0;
	sp.i = 0;
	while (sp.end[sp.i])
	{
		if (sp.end[sp.i] == '\'' || sp.end[sp.i] == '\"')
		{
			if (sp.in_quotes && sp.end[sp.i] == sp.quote_char)
			{
				sp.in_quotes = 0;
				sp.quote_char = '\0';
			}
			else if (!sp.in_quotes)
			{
				sp.in_quotes = 1;
				sp.quote_char = sp.end[sp.i];
			}
			sp.escaped = 0;
		}
		else if (sp.end[sp.i] == '\\')
		{
			if (sp.in_quotes)
			{
				sp.escaped = !sp.escaped;
			}
		}
		else if ((!sp.in_quotes && ft_strchr(delimiters, sp.end[sp.i]) != NULL)
			|| (!sp.in_quotes && (sp.end[sp.i] == ' ' || sp.end[sp.i] == '\t')))
		{
			if (sp.start != sp.end)
			{
				if (sp.token_count >= sp.max_tokens)
				{
					sp.max_tokens *= 2;
					sp.new_tokens = malloc_((sp.max_tokens * sizeof(char *)), NULL, 0, NULL);
					if (!sp.new_tokens)
					{
						printf("allocation err\n");
						exit(1);
					}
					sp.i = 0;
					while (sp.i < sp.token_count)
					{
						sp.new_tokens[sp.i] = sp.tokens[sp.i];
						sp.i++;
					}
					sp.tokens = sp.new_tokens;
				}
				sp.tokens[sp.token_count] = malloc_(((sp.end - sp.start + 1) * sizeof(char)), NULL, 0, NULL);
				if (!sp.tokens[sp.token_count])
				{
					printf("allocation err\n");
					exit(1);
				}
				strncpy(sp.tokens[sp.token_count], sp.start, sp.end - sp.start);
				sp.tokens[sp.token_count][sp.end - sp.start] = '\0';
				sp.token_count++;
			}
			if (ft_strchr(delimiters, sp.end[sp.i]) != NULL)
			{
				if (sp.token_count >= sp.max_tokens)
				{
					sp.max_tokens *= 2;
					sp.new_tokens = malloc_((sp.max_tokens * sizeof(char *)), NULL, 0, NULL);
					if (!sp.new_tokens)
					{
						printf("allocation err\n");
						exit(1);
					}
					sp.i = 0;
					while (sp.i < sp.token_count)
					{
						sp.new_tokens[sp.i] = sp.tokens[sp.i];
						sp.i++;
					}
					sp.tokens = sp.new_tokens;
				}
				sp.tokens[sp.token_count] = malloc_((2 * sizeof(char)), NULL, 0, NULL);
				if (!sp.tokens[sp.token_count])
				{
					printf("allocation err\n");
					exit(1);
				}
				sp.tokens[sp.token_count][0] = sp.end[sp.i];
				sp.tokens[sp.token_count][1] = '\0';
				sp.token_count++;
			}
			sp.start = sp.end + 1;
		}
		else if (sp.escaped)
		{
			sp.escaped = 0;
		}
		sp.end++;
	}
	if (sp.start != sp.end)
	{
		if (sp.token_count >= sp.max_tokens)
		{
			sp.max_tokens *= 2;
			sp.new_tokens = malloc_((sp.max_tokens * sizeof(char *)), NULL, 0, NULL);
			if (!sp.new_tokens)
			{
				printf("allocation err\n");
				exit(1);
			}
			sp.i = 0;
			while (sp.i < sp.token_count)
			{
				sp.new_tokens[sp.i] = sp.tokens[sp.i];
				sp.i++;
			}
			sp.tokens = sp.new_tokens;
		}
		sp.tokens[sp.token_count] = malloc_(((sp.end - sp.start + 1) * sizeof(char)), NULL, 0, NULL);
		if (!sp.tokens[sp.token_count])
		{
			printf("allocation err\n");
			exit(1);
		}
		ft_strncpy(sp.tokens[sp.token_count], sp.start, sp.end - sp.start);
		sp.tokens[sp.token_count][sp.end - sp.start] = '\0';
		sp.token_count++;
	}
	sp.tokens[sp.token_count] = NULL;
	return (sp.tokens);
}
