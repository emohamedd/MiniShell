/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haarab <haarab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 18:42:46 by haarab            #+#    #+#             */
/*   Updated: 2023/09/17 18:44:40 by haarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_redirection(char *arg)
{
	if (!ft_strncmp(">>", arg, ft_strlen(arg)) \
		|| !ft_strncmp("<<", arg, ft_strlen(arg)) \
		|| !ft_strncmp(">", arg, ft_strlen(arg)) \
		|| !ft_strncmp("<", arg, ft_strlen(arg))) {
			return (1);
		}
	return (0);
}

char **clear_cmds_arg_from_direct(char **args)
{
	int count = 0;
	int size = 0;
	while (args[count]) {
		if (is_redirection(args[count])) {
			size++;
		}
		count++;
	}
	char **stack_args = malloc(sizeof(char *) * (lenght_of_the_2d(args) - (size * 2) + 1));
	count = 0;
	size = 0;
	while (args[count]) {
		if ((count == 0 && !is_redirection(args[count])) || (!is_redirection(args[count]) && !is_redirection(args[count - 1]))) {
			stack_args[size] = args[count];
			size++;
		}
		count++;
	}
	 stack_args[size]  = 0;
	return stack_args;
}

char **get_redirectinsv(int size, char **old_stack)
{
	char **stack = malloc(sizeof(char *) * (size + 1));
	int suui = 0;
	int count = 0;
	while (old_stack[count] && suui < size) {
		if (is_redirection(old_stack[count])) {
			stack[suui] = old_stack[count];
			suui++;
		}
		count++;
	}
	stack[suui] = 0;
	return stack;
}

char **get_files(int size, char **old_stack)
{
	char **stack = malloc(sizeof(char *) * (size + 1));
	int suui = 0;
	int count = 0;
	while (old_stack[count] && suui < size) {
		if (is_redirection(old_stack[count])) {
			stack[suui] = old_stack[count +1];
			suui++;
		}
		count++;
	}
	stack[suui] = 0;
	return stack;
}