#include "minishell.h"

char	**ft_find_path()
{
	int		i;
	char	**path;

	i = 0;
	while(g_env[i])
	{
		if((ft_strncmp(g_env[i], "PATH=", 5) == 0))
			path = ft_split(&g_env[i][5], ':');
		i++;
	}
	return(path);
}

void	ft_pipe(char *cm)
{
	int		pipefd[2];
	char	**cmd;
	char	**path;

	path = ft_find_path();
	cmd = ft_split(cm, '|');
	pipe(pipefd);
	fork_process(pipefd, cmd, path, 0);
}