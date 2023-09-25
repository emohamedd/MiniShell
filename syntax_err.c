/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haarab <haarab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 17:01:08 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/24 19:29:14 by haarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int syntax_err(char **args, t_vars *vars)
{
	if (command_notfound(args, vars) > 0)
	{
		printf ("minishell: command not found\n");
		vars->exit_status = 0;
		return (1);
	}
	if (syntax_errors(args, vars) > 0)
	{
		printf ("minishell: syntax error\n");
		vars->exit_status = 2;
		return (1);
	}
	return (0);
}

// void syn_err(char **str, t_vars *vars) 
// {
    
//     int i = 0;
//     while (str[i]) 
//     {
//         int j = 0;
//         while (str[i][j]) 
//         {
//             if (is_special_char(str[i][j])) 
//             {
//                 printf("minishell: syntax error\n");
//                 vars->exit_status = 2;
//             } 
//             else if (str[i][j] == '\'' || str[i][j] == '\"') 
//             {
//                 char quote = str[i][j];
//                 int k = j + 1;
//                 while (str[i][k] && str[i][k] != quote) 
//                 {
//                     k++;
//                 }
//                 if (!str[i][k]) 
//                 {
//                      printf("minishell: syntax error\n");
//                     vars->exit_status = 2;
//                 }
//                 j = k;
//             }
//             j++;
//         }
//         i++;
//     }
// }
void syn_err(char **str, t_vars *vars)
{

    int i = 0;
    int j = 0;
    while(str[i])
    {
        while(str[i][j])
        {
            if((str[i][0] == '>' || str[i][j] == '|'))
            {
                printf("minishell: syntax error\n");
                vars->exit_status = 2;
            }
            j++;
        }
        i++;
    }
}