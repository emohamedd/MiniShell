/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 18:05:55 by emohamed          #+#    #+#             */
/*   Updated: 2023/07/30 19:29:42 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char **split_input(char *str)
{
    char **token = ft_split(str, ' ');
    if (!token)
    {
        perror("Error\n");
        exit(0);
    }
    
}
