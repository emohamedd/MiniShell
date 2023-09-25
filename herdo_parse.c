/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdo_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 19:08:39 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/25 15:46:12 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**red_to_herdoc(char **tokens)
{
	int		len;
	char	**new_tokens;
	int		i;
	int		j;

	len = lenght_of_the_2d(tokens) + 1;
	new_tokens = (char **)malloc(sizeof(char *) * len);
	i = 0;
	j = 0;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], ">") == 0 || ft_strcmp(tokens[i], "<") == 0)
		{
			new_tokens[j] = (char *)malloc(sizeof(char) * (ft_strlen(tokens[i])
						+ 1));
			strcpy(new_tokens[j], tokens[i]);
			while (tokens[i + 1] && (ft_strcmp(tokens[i], tokens[i + 1]) == 0))
			{
				strcat(new_tokens[j], tokens[i + 1]);
				i++;
			}
			j++;
		}
		else
		{
			new_tokens[j] = (char *)malloc(ft_strlen(tokens[i]) + 1);
			strcpy(new_tokens[j], tokens[i]);
			j++;
		}
		i++;
	}
	new_tokens[i] = NULL;
	return (new_tokens);
}
