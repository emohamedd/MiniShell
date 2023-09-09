/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 12:31:48 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/09 12:41:25 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *env(char *envp[])
{
    int i = 0;
    char *envp_var = envp[i];
    
    while(envp_var)
    {
        envp_var = envp[i];
        i++;
    }
    char *key = ft_split_token(envp_var, '=');
    return envp_var;
}

int main(int ac, char **av, char *envp[])
{
    env(envp);
}