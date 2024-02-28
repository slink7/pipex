/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 19:05:41 by scambier          #+#    #+#             */
/*   Updated: 2024/02/28 19:45:25 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

#include "libft.h"
#include "str_exec.h"

int	main(int argc, char **argv, char **envp)
{
	int	files[2];
	int	pipe_[2];
	int	pids[2];
	int	ret;

	if (argc != 5)
		return (1);
	if (pipe(pipe_) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pids[0] = fork();
	if (pids[0] == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pids[0] != 0)
	{
		files[1] = open(argv[4], O_TRUNC | O_CREAT | O_WRONLY, 0644);
		if (files[1] < 0)
		{
			perror("pipex: output");
			exit(EXIT_FAILURE);
		}
		dup2(pipe_[0], 0);
		close(pipe_[1]);
		dup2(files[1], 1);
		ret = str_exec(argv[3], envp);
		close(pipe_[0]);
		close(files[1]);
		if (ret)
			exit(EXIT_FAILURE);
	}
	else
	{
		files[0] = open(argv[1], O_RDONLY);
		if (files[0] < 0)
		{
			perror("pipex: input");
			exit(EXIT_FAILURE);
		}
		dup2(pipe_[1], 1);
		close(pipe_[0]);
		dup2(files[0], 0);
		ret = str_exec(argv[2], envp);
		close(pipe_[1]);
		close(files[0]);
		if (ret)
			exit(EXIT_FAILURE);
	}
	wait(0);
	return (0);
}
