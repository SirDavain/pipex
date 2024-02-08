/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dulrich <dulrich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:09:30 by dulrich           #+#    #+#             */
/*   Updated: 2024/02/08 13:29:27 by dulrich          ###   ########.fr       */
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
	if (!paths)
		return (NULL);
	return (paths);
}

char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		if (!tmp)
			return (NULL);
		command = ft_strjoin(tmp, cmd);
		if (!command)
			return (NULL);
		free(tmp);
		if (access(command, F_OK) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

void	start_child1(t_pipex pipex, char **argv, char **envp)
{
	int	i;

	dup2(pipex.pipe[1], STDOUT_FILENO);
	close(pipex.pipe[0]);
	if (pipex.infile < 0)
		infile_invalid(pipex);
	dup2(pipex.infile, STDIN_FILENO);
	pipex.cmd_args = ft_split(argv[2], ' ');
	if (!pipex.cmd_args)
		return ;
	pipex.cmd = get_cmd(pipex.paths, pipex.cmd_args[0]);
	if (!pipex.cmd)
	{
		i = 0;
		while (pipex.paths[i])
		{
			free(pipex.paths[i]);
			i++;
		}
		free(pipex.paths);
		free_child(&pipex);
		pipe_error("Error while getting commands.\n");
	}
	execve(pipex.cmd, pipex.cmd_args, envp);
}

void	start_child2(t_pipex pipex, char **argv, char **envp)
{
	int	i;

	dup2(pipex.pipe[0], STDIN_FILENO);
	close(pipex.pipe[1]);
	dup2(pipex.outfile, STDOUT_FILENO);
	pipex.cmd_args = ft_split(argv[3], ' ');
	if (!pipex.cmd_args)
		return ;
	pipex.cmd = get_cmd(pipex.paths, pipex.cmd_args[0]);
	if (!pipex.cmd)
	{
		i = 0;
		while (pipex.paths[i])
		{
			free(pipex.paths[i]);
			i++;
		}
		free(pipex.paths);
		free_child(&pipex);
		pipe_error("Error while getting commands.\n");
	}
	execve(pipex.cmd, pipex.cmd_args, envp);
}
