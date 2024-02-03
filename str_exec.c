/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 19:43:56 by scambier          #+#    #+#             */
/*   Updated: 2024/02/03 20:01:23 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#include "libft.h"

static char	*strarr_prefixchr(char **strarr, char *target)
{
	while (ft_strncmp(target, *strarr, ft_strlen(target)))
		strarr++;
	return (*strarr);
}

static char	*get_cmd(char **paths, char *cmd)
{
	char	*temp;
	char	*out;

	while (*paths)
	{
		temp = ft_strjoin(*paths, "/");
		out = ft_strjoin(temp, cmd);
		free(temp);
		if (access(out, 0) == 0)
			return (out);
		free(out);
		paths++;
	}
	return (0);
}

int	str_exec(char *str, char **envp)
{
	static char	**paths = 0;
	char		**argv;
	char		*cmd;
	int			ret;

	paths = ft_split(strarr_prefixchr(envp, "PATH") + 5, ':');
	argv = ft_split(str, ' ');
	cmd = get_cmd(paths, argv[0]);
	ft_strarrfree(paths);
	ret = execve(cmd, argv, envp);
	free(cmd);
	ft_strarrfree(argv);
	return (ret);
}
