/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 13:10:25 by emohamed          #+#    #+#             */
/*   Updated: 2023/07/30 19:34:54 by emohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main()
{
    char *input;
    char **str;
    while(1)
    {
        int i = 0;
        display_prompt();
        input = read_input();
        str = ft_split(input, ' ');
        int j = count_s_lenght(input, ' ');
        
    // Replace "ls" with any shell command you want to execute

        const char* command = str[i];

        // Execute the command using system()
        int status = system(command);
        printf ("str ==== %d\n", status);
        // Check the return value to see if the command executed successfully
        if (status == 0) {
            printf("Command executed successfully.\n");
        } else {
            printf("Command execution failed.\n");
        }

        while (i < j)
        {
            printf("%s\n", str[i]);
            i++;   
        }
    }
    return 0;
}
