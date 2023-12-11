/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dulrich <dulrich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:08:46 by dulrich           #+#    #+#             */
/*   Updated: 2023/12/11 16:50:30 by dulrich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int	fd[2];
	
	if (argc != 5)
		pipe_error("Not the right amount of arguments.");
	open_pipe(&fd);
	
	new_fork_process(argv[2], &fd, envp);
	
	close_fd again
	waitpid(children)
	return (0);
}