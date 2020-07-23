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
	DIR				*dp;
	struct dirent	*entry;
	struct stat		buf;
	char			*res;
	int				i;

	dp = NULL;
	entry = NULL;
	i = -1;
	res = 0;
	while (path[++i])
	{
		if ((dp = opendir(path[i])) != NULL)
		{
			while ((entry = readdir(dp)) != NULL)
			{
				lstat(entry->d_name, &buf);
				if (S_ISDIR(buf.st_mode)
				&& (ft_strcmp(entry->d_name, cmd[0]) == 0))
				{
					res = ft_strjoin_sh(path[i], cmd[0]);
					break ;
				}
			}
			closedir(dp);
		}
	}
	res = ft_relative_path(path, cmd, res, buf);
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
