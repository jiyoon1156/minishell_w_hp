#include "minishell.h"

int		parse_err(char *ptr, int c)
{
	if (*ptr == (c * (-1)))
	{
		(c == '>') ? ft_putstr_fd("parse error near `>'\n", 2) :
		ft_putstr_fd("parse error near `<'\n", 2);
		g_ret = 127;
		return (0);
	}
	return (0);
}

void	read_env(char **info, int fd)
{
	if ((g_ret = ft_env_valid(info)) == 0)
		ft_env(info, fd);
	else
		ft_putstr_fd("No such file or directory\n", 2);
}

void	ft_cmd_fork(char *path_cmd, char **info, int fd)
{
	int		pid;
	int		status;
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

void	read_cmd(char **info, int fd)
{
	char *path_cmd;

	if (ft_strcmp(info[0], "echo") == 0)
		g_ret = (info[1] && ft_strchr(info[1], '$')) ? ft_print_env_1(info) :
		ft_echo(info, fd);
	else if (ft_strcmp(info[0], "cd") == 0)
		g_ret = ft_cd(info);
	else if (ft_strcmp(info[0], "pwd") == 0)
		g_ret = ft_pwd(fd);
	else if (ft_strcmp(info[0], "unset") == 0)
		g_ret = (info[1]) ? ft_unset(info, g_env)
		: ft_ret("unset: not enough arguments\n", 1);
	else if (ft_strcmp(info[0], "export") == 0)
		g_ret = (!info[1]) ? ft_print_env(g_env, fd)
		: ft_export(info, g_env);
	else if (ft_strcmp(info[0], "env") == 0)
		read_env(info, fd);
	else if (ft_strcmp(info[0], "exit") == 0)
		exit(0);
	else if ((path_cmd = ft_pathjoin(ft_find_path(), info)))
		ft_cmd_fork(path_cmd, info, fd);
	else
	{
		g_ret = ft_ret("command not found\n", 127);
		free(path_cmd);
		path_cmd = 0;
	}
}

int		ft_cmd(char **info)
{
	int	i;
	int r_flag;
	int fd;

	i = 0;
	r_flag = 0;
	fd = 1;
	while (info[i])
	{
		if (*info[i] == ('>' * (-1)))
		{
			if (*info[++i] == ('>' * (-1)))
			{
				r_flag = 1;
				if (*info[++i] == ('>' * (-1)) && !(parse_err(info[i], '>')))
					return (0);
			}
			fd = redirection(info[i], r_flag);
		}
		else if (*info[i] == L_REDIR)
		{
			if (*info[++i] == ('<' * (-1)) && !(parse_err(info[i], '<')))
				return (0);
		}
		i++;
	}
	read_cmd(info, fd);
	return (0);
}
