/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   giga_split_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 18:35:35 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/30 18:39:04 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sp	realloc_tokens(t_sp sp)
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
	return (sp);
}

t_sp	handle_token(t_sp sp)
{
	if (sp.token_count >= sp.max_tokens)
	{
		sp = realloc_tokens(sp);
	}
	sp.tokens[sp.token_count] = malloc_(((sp.end - sp.start + 1)
				* sizeof(char)), NULL, 0, NULL);
	if (!sp.tokens[sp.token_count])
	{
		printf("allocation err\n");
		exit(1);
	}
	strncpy(sp.tokens[sp.token_count], sp.start, sp.end - sp.start);
	sp.tokens[sp.token_count][sp.end - sp.start] = '\0';
	sp.token_count++;
	return (sp);
}

t_sp	handle_last_token(t_sp sp)
{
	if (sp.start != sp.end)
	{
		if (sp.token_count >= sp.max_tokens)
		{
			sp = realloc_tokens(sp);
		}
		sp.tokens[sp.token_count] = malloc_(((sp.end - sp.start + 1)
					* sizeof(char)), NULL, 0, NULL);
		if (!sp.tokens[sp.token_count])
		{
			printf("allocation err\n");
			exit(1);
		}
		ft_strncpy(sp.tokens[sp.token_count], sp.start, sp.end - sp.start);
		sp.tokens[sp.token_count][sp.end - sp.start] = '\0';
		sp.token_count++;
	}
	return (sp);
}
