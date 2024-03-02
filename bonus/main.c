/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 19:05:41 by scambier          #+#    #+#             */
/*   Updated: 2024/03/02 23:37:51 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

#include "libft.h"
#include "str_exec.h"

#define WRITE_FLAGS 577

typedef struct s_command {
	char	*command;
	int		fd_in;
	int		fd_out;
}	t_command;

int	execute_command(t_command *cmd, char **envp)
{
	int	out;

	dup2(cmd->fd_in, 0);
	dup2(cmd->fd_out, 1);
	out = str_exec(cmd->command, envp);
	close(cmd->fd_in);
	close(cmd->fd_out);
	return (out);
}

void	pipe_exe(int cmdc, t_command *cmds, char **envp)
{
	int	pid;
	int	fd_pipe[2];

	if (cmdc < 2)
		return ;
	if (pipe(fd_pipe) == -1)
		perror("pipex: pipe");
	pid = fork();
	if (pid == -1)
		perror("pipex: fork");
	else if (pid == 0)
	{
		cmds[0].fd_out = fd_pipe[1];
		close(fd_pipe[0]);
		execute_command(&cmds[0], envp);
	}
	else
	{
		cmds[1].fd_in = fd_pipe[0];
		close(fd_pipe[1]);
		if (cmdc == 2)
			execute_command(&cmds[1], envp);
		else
			pipe_exe(cmdc - 1, cmds + 1, envp);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_command	*cmds;
	int			k;

	cmds = malloc(sizeof(t_command) * (argc - 3));
	if (!cmds)
		exit(EXIT_FAILURE);
	cmds[0].fd_in = open(argv[1], O_RDONLY);
	k = -1;
	while (++k < argc - 3)
		cmds[k].command = argv[k + 2];
	cmds[argc - 4].fd_out = open(argv[argc - 1], WRITE_FLAGS, 0644);
	pipe_exe(argc - 3, cmds, envp);
	close(cmds[0].fd_in);
	close(cmds[argc - 4].fd_out);
	wait(0);
	return (0);
}
