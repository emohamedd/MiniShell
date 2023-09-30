/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 20:32:31 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/30 02:40:18 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**make_token(char *s)
{
	char	*special_chars;
	char	**tokens;
	char	**quote;

	special_chars = "<>|";
	tokens = split(s, special_chars);
	quote = expand_quotes(tokens);
	return (red_to_herdoc(tokens));
}
