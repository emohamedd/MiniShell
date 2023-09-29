/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 13:39:24 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/28 17:03:56 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int	count_s_lenght_export(const char *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			j++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (j);
}

char	*allocat_s_export(const char *s, char c)
{
	int		i;
	int		len;
	char	*p;

	i = 0;
	len = 0;
	while (s[len] && s[len] != c)
		len++;
	p = malloc(sizeof(char) * (len + 1));
	// p = malloc_((sizeof(char) * (len + 1)), NULL, 0, NULL);
	if (!p)
		return (NULL);
	while (i < len)
	{
		p[i] = s[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	**ft_split_export(char const *s, char c)
{
	char	**p;
	int		i;
	int		j;

	i = 0;
	j = 0;
	p = ft_calloc(sizeof(char *), count_s_lenght_export(s, c) + 1);
	// p = malloc_((sizeof(char *) * count_s_lenght(s, c) + 1), NULL, 0, NULL);
	
	if (!p)
		return (NULL);
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
		{
			p[j] = allocat_s_export(&s[i], c);
			j++;
		}
		while (s[i] && s[i] != c)
			i++;
	}
	return (p);
}

