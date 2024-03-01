/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 19:05:41 by scambier          #+#    #+#             */
/*   Updated: 2024/03/01 20:22:34 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

#include "libft.h"
#include "str_exec.h"

typedef struct s_command {
	char	*command;
	int		fd_in;
	int		fd_out;
}	t_command;

int	exe(t_command *cmd, char **envp)
{
	int	out;

	dup2(cmd->fd_in, 0);
	dup2(cmd->fd_out, 1);
	out = str_exec(cmd->command, envp);
	close(cmd->fd_in);
	close(cmd->fd_out);
	return (out);
}

void	pipe_exe(t_command *cmd1, t_command *cmd2, char **envp)
{
	int	pid;
	int	fd_pipe[2];

	if (pipe(fd_pipe) == -1)
		perror("pipex: pipe");
	pid = fork();
	if (pid == -1)
		perror("pipex: fork");
	else if (pid == 0)
	{
		cmd1->fd_out = fd_pipe[1];
		close(fd_pipe[0]);
		exe(cmd1, envp);
	}
	else
	{
		cmd2->fd_in = fd_pipe[0];
		close(fd_pipe[1]);
		exe(cmd2, envp);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_command	cmd1;
	t_command	cmd2;

	if (argc != 5)
		return (1);
	cmd1.fd_in = open(argv[1], O_RDONLY);
	cmd1.command = argv[2];
	cmd2.command = argv[3];
	cmd2.fd_out = open(argv[4], O_TRUNC | O_CREAT | O_WRONLY, 0644);
	pipe_exe(&cmd1, &cmd2, envp);
	close(cmd1.fd_in);
	close(cmd2.fd_out);
	wait(0);
	return (0);
}
