/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 13:52:14 by hpark             #+#    #+#             */
/*   Updated: 2020/07/23 13:52:15 by hpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_find_path(void)
{
	int		i;
	char	**path;

	i = 0;
	path = 0;
	while (g_env[i])
	{
		if ((ft_strncmp(g_env[i], "PATH=", 5) == 0))
			path = ft_split(&g_env[i][5], ':');
		i++;
	}
	return (path);
}

void	ft_pipe(char *cm)
{
	int		pipefd[2];
	char	**cmd;
	char	**path;

	path = ft_find_path();
	cmd = get_cmds(cm, '|');
	pipe(pipefd);
	fork_process(pipefd, cmd, path, 0);
	ft_free(cmd);
	ft_free(path);
}
