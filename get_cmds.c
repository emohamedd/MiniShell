/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haarab <haarab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 10:57:54 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/29 20:58:11 by haarab           ###   ########.fr       */
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
	// dst = malloc(sizeof(char *) * ((*info)->size + 1));
	dst = malloc_((sizeof(char *) * ((*info)->size + 1)), NULL, 0, NULL);
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