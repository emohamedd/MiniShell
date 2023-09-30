/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 10:40:05 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/30 02:24:12 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup_export(const char *s1)
{
	int		i;
	char	*p;

	if (!s1)
		return (0);
	i = 0;
	p = malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (!p)
		return (NULL);
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

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

void	*ft_calloc_export(size_t count, size_t size)
{
	size_t	sizee;
	void	*p;

	p = NULL;
	sizee = count * size;
	p = malloc(sizee);
	if (!p)
		return (NULL);
	ft_bzero(p, sizee);
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
