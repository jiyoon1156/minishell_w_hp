/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_fork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhur <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 13:54:23 by jhur              #+#    #+#             */
/*   Updated: 2020/07/23 13:54:25 by jhur             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_forking(int fd, char *path_cmd, char **av)
{
	int	pid;
	int status;

	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd("fork failed", 2);
		exit(1);
	}
	else if (pid == 0)
	{
		dup2(fd, 1);
		execve(path_cmd, av, g_env);
	}
	else
	{
		waitpid(pid, &status, 0);
		g_ret = status / 256;
		free(path_cmd);
		free(av);
	}
}

void		ft_cmd_fork(char *path_cmd, char **info, int fd)
{
	char	**av;
	int		i;

	av = malloc(sizeof(char *) * (ft_cnt(info) + 1));
	i = 0;
	while (*info)
	{
		if (**info != R_REDIR && **info != L_REDIR)
			av[i++] = *info;
		else if (**(info) == **(info + 1))
			info = info + 2;
		else if (**info == R_REDIR)
			info++;
		info++;
	}
	av[i] = 0;
	ft_forking(fd, path_cmd, av);
}
