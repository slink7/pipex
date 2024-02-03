/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 19:05:41 by scambier          #+#    #+#             */
/*   Updated: 2024/02/03 20:09:01 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#include "libft.h"
#include "str_exec.h"

int	main(int argc, char **argv, char **envp)
{
	int	infile;
	int	outfile;

	infile = open("InFile", O_RDONLY);
	outfile = open("OutFile", O_CREAT | O_WRONLY);
	dup2(infile, 0);
	dup2(outfile, 1);
	str_exec(argv[1], envp);
}
