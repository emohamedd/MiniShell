/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 11:02:17 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/30 15:36:26 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_var_key(char *key, t_vars *vars)
{
	char	*exp_value;

	exp_value = ft_getenv(key, vars);
	if (!exp_value)
	{
		exp_value = "";
	}
	return (exp_value);
}

char	*expand_var(char *arg, t_vars *vars)
{
	t_ev	ev;

	ev.i = 0;
	while (ev.i < ft_strlen(arg))
	{
		if (arg[ev.i] == '$' && !is_var_inside_sq(arg, ev.i))
		{
			ev.dst1 = ft_strndup(arg, ev.i);
			if (arg[ev.i + 1] && (arg[ev.i + 1] == '?'))
			{
				ev.i++;
				ev.exp_value = ft_itoa(exit_status);
			}
			else
			{
				ev.key = ft_strndup(&arg[ev.i + 1], get_var_size(&arg[ev.i + 1]));
				ev.exp_value = ft_getenv(ev.key, vars);
				if (!ev.exp_value)
					ev.exp_value = "";
			}
			ev.dst3 = arg + ((ev.i + 1) + get_var_size(&arg[ev.i + 1]));
			ev.dst2 = ft_strjoin(ev.dst1, ev.exp_value);
			arg = ft_strjoin(ev.dst2, ev.dst3);
			ev.i = 0;
		}
		ev.i++;
	}
	return (arg);
}
