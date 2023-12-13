/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dulrich <dulrich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:09:30 by dulrich           #+#    #+#             */
/*   Updated: 2023/12/13 09:28:50 by dulrich          ###   ########.fr       */
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

void	close_pipes(t_pipex *pipex)
{
	close(pipex->pipe[0]);
	close(pipex->pipe[1]);
}

char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, F_OK) == 0)
			return(command);
		free(command);
		paths++;
	}
	return (NULL);
}

void	free_parent(t_pipex *pipex)
{
	int	i;

	close(pipex->infile);
	close(pipex->outfile);
	i = 0;
	while (pipex->paths[i])
	{
		free(pipex->paths[i]);
		i++;
	}
	free(pipex->paths);
}

void	free_child(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->cmd_args[i])
	{
		free(pipex->cmd_args[i]);
		i++;
	}
	free(pipex->cmd_args);
	free(pipex->cmd);
}

void	start_child1(t_pipex pipex, char **argv, char **envp)
{
	dup2(pipex.pipe[1], STDOUT_FILENO);
	close(pipex.pipe[0]);
	dup2(pipex.infile, STDIN_FILENO);
	pipex.cmd_args = ft_split(argv[2], ' ');
	pipex.cmd = get_cmd(pipex.paths, pipex.cmd_args[0]);
	if (!pipex.cmd)
	{
		free_child(&pipex);
		pipe_error("Error while getting commands.");
	}
	execve(pipex.cmd, pipex.cmd_args, envp);
}

void	start_child2(t_pipex pipex, char **argv, char **envp)
{
	dup2(pipex.pipe[0], STDIN_FILENO);
	close(pipex.pipe[1]);
	dup2(pipex.outfile, STDOUT_FILENO);
	pipex.cmd_args = ft_split(argv[3], ' ');
	pipex.cmd = get_cmd(pipex.paths, pipex.cmd_args[0]);
	if (!pipex.cmd)
	{
		free_child(&pipex);
		pipe_error("Error while getting commands.");
	}
	execve(pipex.cmd, pipex.cmd_args, envp);
}
