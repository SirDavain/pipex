/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dulrich <dulrich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:08:46 by dulrich           #+#    #+#             */
/*   Updated: 2023/12/11 23:02:47 by dulrich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int	pipe1[2];
	int	pipe2[2];
	
	if (argc != 5)
		pipe_error("Not the right amount of arguments.");
	open_pipe(&pipe1);
	open_pipe(&pipe2);
	
	new_fork_process(argv[2], &pipe2, &pipe1, envp);
	
	close_fd(pipe1[1], pipe2[1]);
	waitpid(children);
	return (0);
}