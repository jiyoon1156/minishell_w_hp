#include "minishell.h"

static char	*ft_absolute_path(char **path, char **cmd,
char *res, struct stat buf)
{
	path = 0;
	if (res == 0 && lstat(cmd[0], &buf) == 0)
	{
		res = ft_strdup(cmd[0]);
		g_ret = 1;
	}
	return (res);
}

char		*ft_pathjoin(char **path, char **cmd)
{
	struct stat		buf;
	char			*res;
	int				i;
	char			*path_cmd;

	i = 0;
	res = 0;
	path_cmd = 0;
	while (path[i])
	{
		path_cmd = ft_strjoin_sh(path[i], cmd[0]);
		if (lstat(path_cmd, &buf) == 0)
		{
			res = path_cmd;
			break ;
		}
		free(path_cmd);
		path_cmd = 0;
		i++;
	}
	ft_free(path);
	if (res == 0)
		res = ft_absolute_path(path, cmd, res, buf);
	return (res);
}

void		child_process(char **info, int *pipefd)
{
	if (pipefd[0] != 0)
		close(pipefd[0]);
	dup2(pipefd[1], 1);
	if (pipefd[1] != 1)
		close(pipefd[1]);
	ft_cmd(info);
	exit(0);
}

void		parent_process(int *pipefd, char **path, char **cmd, int i)
{
	int		pipefd2[2];

	close(pipefd[1]);
	dup2(pipefd[0], 0);
	close(pipefd[0]);
	pipefd2[0] = 0;
	pipefd2[1] = 1;
	if (cmd[i + 1] != 0)
		pipe(pipefd2);
	fork_process(pipefd2, cmd, path, i);
}

void		fork_process(int *pipefd, char **cmd, char **path, int i)
{
	int		pid;
	int		status;
	char	**info;

	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		exit(1);
	}
	else if (pid == 0)
	{
		info = get_info(cmd[i]);
		child_process(info, pipefd);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (cmd[i + 1])
			parent_process(pipefd, path, cmd, i + 1);
	}
}
