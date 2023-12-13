/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dulrich <dulrich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:08:46 by dulrich           #+#    #+#             */
/*   Updated: 2023/12/13 09:27:02 by dulrich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	
	if (argc != 5)
		pipe_error("Not the right amount of arguments.");
	pipex.infile = open(argv[1], O_RDONLY);
	if (pipex.infile < 0)
		pipe_error("Error with the infile.");
	pipex.outfile = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, "rw-r--r--");
	if (pipex.outfile < 0)
		pipe_error("Error with the outfile.");
	if (pipe(pipex.pipe) < 0)
		pipe_error("Error when establishing pipe.");
	pipex.paths = get_path(envp);
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		start_child1(pipex, argv, envp);
	pipex.pid2 = fork();
	if (pipex.pid2 == 0)
		start_child2(pipex, argv, envp);
	close_pipes(&pipex);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	free_parent(&pipex);
	return (0);
}
