/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dulrich <dulrich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:08:46 by dulrich           #+#    #+#             */
/*   Updated: 2024/02/05 15:49:14 by dulrich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipe_error(char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
	exit(1);
}

void	close_pipes(t_pipex *pipex)
{
	close(pipex->pipe[0]);
	close(pipex->pipe[1]);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc != 5)
		pipe_error("Not the right amount of arguments.\n");
	pipex.infile = open(argv[1], O_RDONLY);
	if (pipex.infile < 0)
		ft_printf("No such file or directory: %s\n", argv[1]);
	pipex.outfile = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (pipex.outfile < 0)
		pipe_error("Error with the outfile.\n");
	if (pipe(pipex.pipe) < 0)
		pipe_error("Error when establishing pipe.\n");
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
