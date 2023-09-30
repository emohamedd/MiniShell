/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocat_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 11:03:07 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/30 04:43:17 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_info	**allocat_token(char **s, t_vars *vars)
{
	int		i;
	t_info	**inf;

	i = 0;
	inf = malloc_((sizeof(t_info *) * (lenght_of_the_2d(s) + 1)), NULL, 0,
			NULL);
	if (!inf)
	{
		printf("Err\n");
		exit(1);
	}
	inf[lenght_of_the_2d(s)] = NULL;
	while (s[i])
	{
		inf[i] = malloc_((sizeof(t_info)), NULL, 0, NULL);
		inf[i]->content = s[i];
		inf[i]->size = lenght_of_the_2d(s);
		inf[i]->content = expand_var(inf[i]->content, vars);
		inf[i]->lenght = ft_strlen(inf[i]->content);
		i++;
	}
	return (inf);
}
