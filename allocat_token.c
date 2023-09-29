/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocat_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 11:03:07 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/29 11:03:15 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_info	**allocat_token(char **s, t_vars *vars)
{
	int		i;
	t_info	**inf;
	char	*trimmed_content;
	char	*var;

	i = 0;
	// inf = malloc(sizeof(t_info *) * (lenght_of_the_2d(s) + 1));
	inf = malloc_((sizeof(t_info *) * (lenght_of_the_2d(s) + 1)), NULL, 0, NULL);
	if (!inf)
	{
		printf("Err\n");
		exit(1);
	}
	while (s[i])
	{
		// inf[i] = malloc(sizeof(t_info));
		inf[i] = malloc_((sizeof(t_info)), NULL, 0, NULL);
		inf[i]->content = s[i];
		inf[i]->size = lenght_of_the_2d(s);
		inf[i]->content = expand_var(inf[i]->content, vars);
		 if (inf[i]->content[0] == '<')
			inf[i]->type = "RDIN";
		else if (inf[i]->content[0] == '>')
			inf[i]->type = "RDOUT";
		else if (inf[i]->content[0] == '|')
			inf[i]->type = "PIPE";
		else if (inf[i]->content[0] == '\"')
			inf[i]->type = "DBCOTE";
		if (inf[i]->content[0] == '\'')
			inf[i]->type = "SGCOTE";
		else if (is_char(s[i]))
			inf[i]->type = "STR";
		inf[i]->lenght = ft_strlen(inf[i]->content);
		i++;
	}
	return (inf);
}
