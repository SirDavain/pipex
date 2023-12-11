/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dulrich <dulrich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:09:30 by dulrich           #+#    #+#             */
/*   Updated: 2023/12/11 23:36:22 by dulrich          ###   ########.fr       */
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
	ft_putstr_fd(str, STDERR_FILENO);
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

void	new_fork_process(char *cmd, int (*p1)[2], int (*p2)[2], char **env)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		pipe_error("Error while forking.");
	if (pid == 0)
	{
		close_fd((*p1)[1], (*p2)[0]);
		exec_pipe(cmd, (*p1)[0], (*p2)[1], env);
	}
	open_pipe(p1);
}

void	exec_pipe(char *bin, int fd_in, int fd_out, char **env)
{
	char	**paths;
	char	**args;

	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	paths = get_path(env);
	args = ft_split(bin, ' ');

}

char	*get_access(char *cmd, char **paths)
{
	char	*path;

	
}
