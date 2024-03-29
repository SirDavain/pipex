/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dulrich <dulrich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 13:22:11 by dulrich           #+#    #+#             */
/*   Updated: 2024/02/08 13:29:19 by dulrich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./libft/libft.h"
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <stdio.h>
# include <stdarg.h>
# include <stdint.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/uio.h>

typedef struct s_pipex
{
	pid_t	pid1;
	pid_t	pid2;
	int		infile;
	int		outfile;
	int		pipe[2];
	char	**cmd_args;
	char	**paths;
	char	*cmd;
}				t_pipex;

// Main:
int		main(int argc, char **argv, char **envp);
void	close_pipes(t_pipex *pipex);
void	pipe_error(char *str);
void	infile_invalid(t_pipex pipex);

// Utilities:
char	**get_path(char **env);
char	*get_cmd(char **paths, char *cmd);
void	start_child1(t_pipex pipex, char **argv, char **envp);
void	start_child2(t_pipex pipex, char **argv, char **envp);

// Free
void	free_parent(t_pipex *pipex);
void	free_child(t_pipex *pipex);

#endif