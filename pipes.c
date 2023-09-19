/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haarab <haarab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 18:35:50 by haarab            #+#    #+#             */
/*   Updated: 2023/09/18 17:04:00 by haarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void pipe_commands(t_vars *vars, int i) 
{
	int status;
	char *path;
    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) 
    {
        perror("pipe");
        exit(1);
    }


	pid_t child1;
	child1 = fork();
	if (child1 == -1) 
	{
		perror("fork");
		exit(1);
	}
	if (child1 == 0) 
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		// if (dup2(pipe_fd[1], STDOUT_FILENO) == -1) 
		// {
		// 	perror("dup2");
		// 	exit(1);
		// }
		close(pipe_fd[1]);
		path = get_path(vars, vars->cmds[i].cmd);
		execve(path, vars->cmds[i].cmds_args, vars->envp);
		exit(0);
	} 
	else 
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		// if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		// {
		// 	perror("dup2");
		// 	exit(1);
		// }
		close(pipe_fd[0]);
		path = get_path(vars, vars->cmds[i + 1].cmd);
		// int id  = fork();
		// if (id == -1) 
		// {
		// 	perror("fork");
		// 	exit(1);
		// }
		// if (id  == 0)	
		// 	execve(path, vars->cmds[i + 1].cmds_args, vars->envp);
		// else
		// 	waitpid(id, &status, 0);
		waitpid(child1, &status, 0);
	}
}