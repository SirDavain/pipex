/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dulrich <dulrich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 13:22:11 by dulrich           #+#    #+#             */
/*   Updated: 2023/12/12 00:06:47 by dulrich          ###   ########.fr       */
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

typedef struct	s_pipex
{
	pid_t	pid1;
	pid_t	pid2;
	int		infile;
	int		outfile;
	int		pipe[2];
	char	**cmd_paths;
	char	**cmd_args;
	char	*paths;
	char	*cmd;
}				t_pipex;

// Functions:
int	main(int argc, char **argv, char **envp);

// Utilities 1:
void	pipe_error(char *str);
char	**get_path(char **env);
void	open_pipe(int (*p)[2]);
void	close_fd(int fd1, int fd2);
void	new_fork_process(char *cmd, int (*p1)[2], int (*p2)[2], char **env);

#endif