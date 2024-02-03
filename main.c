/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 19:05:41 by scambier          #+#    #+#             */
/*   Updated: 2024/02/03 22:31:32 by scambier         ###   ########.fr       */
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
	int	infile;
	int	outfile;
	int	pipe_[2]; // 0:read 1:write
	int	pids[2];

	infile = open("InFile", O_RDONLY);
	outfile = open("OutFile", O_TRUNC | O_CREAT | O_RDWR, 644);
	if (pipe(pipe_))
		printf("pipe Error\n");
	
	pids[0] = fork();
	if (pids[0] == 0)
	{
		dup2(infile, 0);
		dup2(pipe_[1], 1);
		close(pipe_[0]);
		str_exec(argv[1], envp);
	}
	pids[1] = fork();
	if (pids[1] == 0)
	{
		dup2(pipe_[0], 0);
		dup2(outfile, 1);
		close(pipe_[1]);
		str_exec(argv[2], envp);
	}
	close(pipe_[0]);
	close(pipe_[1]);
	close(infile);
	close(outfile);
	waitpid(pids[0], 0, 0);
	waitpid(pids[1], 0, 0);
}
