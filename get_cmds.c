/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 10:57:54 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/24 11:36:24 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_cmds(t_info **info)
{
	int		len = 0;
	int		i;
	char	*cmd = NULL;

	len = (*info)->size;
	i = 0;
	char **dst = malloc(sizeof(char *) * ((*info)->size + 1));
	while (i < len)
	{
		dst[i] =  info[i]->content;
		i++;
	}
	dst[i] = 0;
	return (dst);
}

// int count = 0;
// while (cmds[count]) {
// 	printf("arg => %s\n", cmds[count]);
// 	count++;
// }
// exit(0);