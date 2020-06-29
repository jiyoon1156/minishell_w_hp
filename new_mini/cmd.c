#include "minishell.h"

int		parse_err(char *ptr, int c)
{
	if (*ptr == (c * (-1)))
	{
		(c == '>') ? ft_puts("parse error near `>'\n") : "";
		g_ret = 127;
		return (0);
	}
	return (0);
}
void	read_env(char **info, int fd)
{
	if (!info[1])
		g_ret = ft_print_env(g_env, fd);
	if (info[1])
	{
		if ((g_ret = ft_env_valid(info)))
			ft_env(info, g_env, fd);
	}
}
void	read_cmd(char **info, int fd)
{
	if (ft_strcmp(info[0], "$?") == 0)
		ft_putnbr_newline(g_ret);
	else if (ft_strcmp(info[0], "echo") == 0)
		g_ret = (ft_strchr(info[1], '$')) ? ft_print_env_1(info) :
		ft_echo(info, redir, r_flag);
	else if (ft_strcmp(info[0], "cd") == 0)
		g_ret = ft_cd(info);
	else if (ft_strcmp(info[0], "pwd") == 0)
		g_ret = ft_pwd(info, redir, r_flag);
	else if (ft_strcmp(info[0], "unset") == 0)
		g_ret = (info[1]) ? ft_unset(info, envp)
		: ft_ret("unset: not enough arguments\n", 1);
	else if (ft_strcmp(info[0], "export") == 0)
		g_ret = (!info[1]) ? ft_print_env(envp, redir, r_flag)
		: ft_export(info, envp, redir, r_flag);
	else if (ft_strcmp(info[0], "env") == 0)
		read_env(info, fd);
	else if (ft_strcmp(info[0], "exit") == 0)
		exit(0);
	else
		g_ret = ft_ret("command not found\n", 127);
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
		i++;
	}
	read_cmd(info, fd);
	///////////////////////////////////////////////////
	// if ((ptr = ft_strchr(cmd, '>')))
	// {
	// 	if (*(ptr + 1) == '>')
	// 		r_flag = 1;
	// 	if ((*(ptr + 2) == '>') && !(parse_err(ptr, '>')))
	// 		return (0);
	// 	redir = ft_split(cmd, '>');
	// 	cmd = redir[0];
	// }
	// if ((ptr = ft_strchr(cmd, '|')))
	// {
	// 	if ((*(ptr + 1) == '|') && !parse_err(ptr, '|'))
	// 		return (0);
	// 	ft_pipe(cmd);
	// }
	// else
	// 	normal_cmd(cmd, redir, r_flag);
	return (0);
}
