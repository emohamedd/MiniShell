/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   giga_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 18:32:00 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/30 21:35:34 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sp	init_sp(t_sp sp, char *s)
{
	sp.token_count = 0;
	sp.start = s;
	sp.end = s;
	sp.in_quotes = 0;
	sp.quote_char = '\0';
	sp.escaped = 0;
	sp.i = 0;
	return (sp);
}

t_sp	handle_quotes(t_sp sp)
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
	return (sp);
}

t_sp	handle_escape(t_sp sp)
{
	if (sp.end[sp.i] == '\\')
	{
		if (sp.in_quotes)
		{
			sp.escaped = !sp.escaped;
		}
	}
	else if (sp.escaped)
	{
		sp.escaped = 0;
	}
	return (sp);
}

t_sp	handle_delimiters(t_sp sp, char *delimiters)
{
	if ((!sp.in_quotes && ft_strchr(delimiters, sp.end[sp.i]) != NULL)
		|| (!sp.in_quotes && (sp.end[sp.i] == ' ' || sp.end[sp.i] == '\t')))
	{
		if (sp.start != sp.end)
			sp = handle_token(sp);
		if (ft_strchr(delimiters, sp.end[sp.i]) != NULL)
		{
			if (sp.token_count >= sp.max_tokens)
				sp = realloc_tokens(sp);
			sp.tokens[sp.token_count] = malloc_((2 * sizeof(char)), NULL, 0,
					NULL);
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
	return (sp);
}

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
	sp = init_sp(sp, s);
	while (sp.end[sp.i])
	{
		sp = handle_quotes(sp);
		sp = handle_escape(sp);
		sp = handle_delimiters(sp, delimiters);
		sp.end++;
	}
	sp = handle_last_token(sp);
	sp.tokens[sp.token_count] = NULL;
	return (sp.tokens);
}
