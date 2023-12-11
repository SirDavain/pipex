/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dulrich <dulrich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:09:30 by dulrich           #+#    #+#             */
/*   Updated: 2023/12/11 16:50:21 by dulrich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_path(char **env)
{
	char	**paths;

	while (*env)
	{
		if (ft_strncmp(*env, "PATH", 4) == 0)
			break ;
		env++;
	}
	paths = ft_split(*env + 5, ':');
	return (paths);
}

void	pipe_error(char *str)
{
	ft_putstr_fd(str, STDERROR_FILENO);
	exit(1);
}

void	close_fd(int fd1, int fd2)
{
	close(fd1);
	close(fd2);
}

void	open_pipe(int (*p)[2])
{
	close_fd((*p)[0], (*p)[1]);
	pipe((*p));
}

void	new_fork_process(char *cmd, int (*p)[2], char **env)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		pipe_error("Error while forking.");
	if (pid == 0)
	{
		dup2((*p)[1], STDOUT_FILENO);
		close_fd()
	}
}
