/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 10:57:54 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/26 22:23:24 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_cmds(t_info **info)
{
	int		len;
	int		i;
	char	*cmd;
	char	**dst;

	len = 0;
	cmd = NULL;
	len = (*info)->size;
	i = 0;
	dst = malloc(sizeof(char *) * ((*info)->size + 1));
	while (i < len)
	{
		dst[i] =  info[i]->content;
		i++;
	}
	dst[i] = 0;
	dst = expand_quotes(dst);
	dst = expand_s_quotes(dst);
	return (dst);
}

// int count = 0;
// while (cmds[count]) {
// 	printf("arg => %s\n", cmds[count]);
// 	count++;
// }
// exit(0);