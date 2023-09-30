/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 17:01:08 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/30 21:38:18 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error(char **str)
{
	int	i;
	int	j;
	int	a;
	int	b;

	i = 0;
	while (str[i])
	{
		j = 0;
		a = 0;
		b = 0;
		while (str[i][j])
		{
			if (str[i][j] == '<')
				a++;
			if (str[i][j] == '>')
				b++;
			j++;
		}
		if (a > 2 || b > 2)
			return (1);
		i++;
	}
	return (0);
}

int	syntax_errors_tree(char **args)
{
	int	i;
	int	j;

	i = 0;
	while (args[i])
	{
		j = 0;
		if (!ft_strncmp(">>", args[i], ft_strlen(args[i]))
			&& args[i + 1] == NULL)
			j++;
		if (!ft_strncmp("|", args[i], ft_strlen(args[i]))
			&& (!ft_strncmp("|", args[i + 1], ft_strlen(args[i + 1]))))
			j++;
		if (j > 0)
			return (j);
		i++;
	}
	return (0);
}

int	syntax_errors_second(char **args)
{
	int	i;
	int	j;

	i = 0;
	while (args[i])
	{
		j = 0;
		if (!ft_strncmp(">>", args[i], ft_strlen(args[i]))
			&& (!ft_strncmp("|", args[i + 1], ft_strlen(args[i + 1]))))
			j++;
		if (!ft_strncmp("<<", args[i], ft_strlen(args[i]))
			&& (!ft_strncmp("|", args[i + 1], ft_strlen(args[i + 1]))))
			j++;
		if (!ft_strncmp("|", args[0], ft_strlen(args[0]) + 1))
			j++;
		if (j > 0)
			return (j);
		i++;
	}
	return (0);
}

int	syntax_errors(char **args)
{
	int	i;
	int	j;

	i = 0;
	while (args[i])
	{
		j = 0;
		if (!ft_strncmp("|", args[i], ft_strlen(args[i]))
			&& args[i + 1] == NULL)
			j++;
		if (!ft_strncmp(">", args[i], ft_strlen(args[i]))
			&& args[i + 1] == NULL)
			j++;
		if (!ft_strncmp("<", args[i], ft_strlen(args[i]))
			&& args[i + 1] == NULL)
			j++;
		if (!ft_strncmp("<<", args[i], ft_strlen(args[i]))
			&& args[i + 1] == NULL)
			j++;
		if (j > 0)
			return (j);
		i++;
	}
	return (0);
}

int	syntax_err(char **args)
{
	if ((syntax_errors_tree(args)) > 0)
	{
		printf("minishell: syntax error\n");
		g_exit_status = 2;
		return (1);
	}
	if ((syntax_errors_second(args)) > 0)
	{
		printf("minishell: syntax error\n");
		g_exit_status = 2;
		return (1);
	}
	if (syntax_errors(args) > 0)
	{
		printf("minishell: syntax error\n");
		g_exit_status = 2;
		return (1);
	}
	if (ft_error(args) > 0)
	{
		printf("minishell: syntax error\n");
		g_exit_status = 2;
		return (1);
	}
	return (0);
}
