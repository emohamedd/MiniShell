/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 11:02:17 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/30 01:51:23 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *expand_var_key(char *key, t_vars *vars) 
{
    char *exp_value = ft_getenv(key, vars);
    if (!exp_value) {
        exp_value = "";
    }
    return exp_value;
}

char *expand_var(char *arg, t_vars *vars) 
{
    int i = 0;
    char *key;
    char *dst1;
    char *dst2;
    char *dst3;
    char *exp_value;

    while (i < ft_strlen(arg)) {
        if (arg[i] == '$' && !is_var_inside_sq(arg, i)) {
            dst1 = ft_strndup(arg, i);
            if (arg[i + 1] && (arg[i + 1] == '?')) {
                i++;
                exp_value = ft_itoa(exit_status);
            } else {
                key = ft_strndup(&arg[i + 1], get_var_size(&arg[i + 1]));
                exp_value = expand_var_key(key, vars);
            }
            dst3 = arg + ((i + 1) + get_var_size(&arg[i + 1]));
            dst2 = ft_strjoin(dst1, exp_value);
            arg = ft_strjoin(dst2, dst3);
            i = 0;
        }
        i++;
    }
    return arg;
}
