/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdo_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 19:08:39 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/30 02:39:27 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_new_tokens_count(char **tokens)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], ">") == 0 || ft_strcmp(tokens[i], "<") == 0)
		{
			count++;
			while (tokens[i + 1] && (ft_strcmp(tokens[i], tokens[i + 1]) == 0))
			{
				i++;
			}
		}
		else
		{
			count++;
		}
		i++;
	}
	return (count);
}

static void	copy_tokens_with_redirections(char **tokens, char **new_tokens)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], ">") == 0 || ft_strcmp(tokens[i], "<") == 0)
		{
			new_tokens[j] = malloc_((sizeof(char) * (ft_strlen(tokens[i]) + 1)),
					NULL, 0, NULL);
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
			new_tokens[j] = malloc_((ft_strlen(tokens[i]) + 1), NULL, 0, NULL);
			strcpy(new_tokens[j], tokens[i]);
			j++;
		}
		i++;
	}
}

char	**red_to_herdoc(char **tokens)
{
	int		new_tokens_count;
	char	**new_tokens;

	new_tokens_count = get_new_tokens_count(tokens);
	new_tokens = malloc_(((new_tokens_count + 1) * sizeof(char *)), NULL, 0,
			NULL);
	if (!new_tokens)
	{
		printf("allocation err\n");
		exit(1);
	}
	copy_tokens_with_redirections(tokens, new_tokens);
	new_tokens[new_tokens_count] = NULL;
	return (new_tokens);
}
