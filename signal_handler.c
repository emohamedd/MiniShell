/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haarab <haarab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 10:55:52 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/23 19:54:50 by haarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void sigintHandler(int signal) 
{
    // if (rl_catch_signals == 1)
    // {
    //     close(0);
    // }
	if (signal == SIGINT)
    {
        printf("\n");
        rl_on_new_line();
        // rl_replace_line("", 0);
        rl_redisplay();
    }
}
