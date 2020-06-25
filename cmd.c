#include "minishell.h"

int		parse_err(char *ptr, int c)
{
	int		i;

	i = (c == '>') ? 2 : 1;
	if (*(ptr + i) == c)
	{
		(c == '>') ? ft_puts("parse error near `>'\n") :
		ft_puts("parse error near `|'\n");
		g_ret = 127;
		return (0);
	}
	return (0);
}

void	normal_cmd(char *cmd, char **redir, int r_flag)
{
	char	**info;

	info = ft_split(cmd, ' ');
	read_cmd(info, redir, r_flag, g_env);
	ft_free(info);
}

int		ft_cmd(char *cmd)
{
	char	*ptr;
	char	**redir;
	int		r_flag;

	redir = 0;
	r_flag = 0;
	if ((ptr = ft_strchr(cmd, '>')))
	{
		if (*(ptr + 1) == '>')
			r_flag = 1;
		if ((*(ptr + 2) == '>') && !(parse_err(ptr, '>')))
			return (0);
		redir = ft_split(cmd, '>');
		cmd = redir[0];
	}
	if ((ptr = ft_strchr(cmd, '|')))
	{
		if ((*(ptr + 1) == '|') && !parse_err(ptr, '|'))
			return (0);
		ft_pipe(cmd);
	}
	else
		normal_cmd(cmd, redir, r_flag);
	return (0);
}

int		newline_valid(char **info)
{
	int		echo_newline_flag;
	char	**cmd;

	echo_newline_flag = 0;
	cmd = ft_split(info[0], ' ');
	if ((ft_strcmp(cmd[1], "-n")) == 0)
		echo_newline_flag = 1;
	ft_free(cmd);
	return (echo_newline_flag);
}

void	read_env(char **info, char **redir, int r_flag)
{
	if (!info[1])
		g_ret = ft_print_env(g_env, redir, r_flag);
	if (info[1])
	{
		if ((g_ret = ft_env_valid(info)))
			ft_env(info, g_env, redir, r_flag);
	}
}

void	read_cmd(char **info, char **redir, int r_flag, char **envp)
{
	if (ft_strcmp(info[0], "$?") == 0)
		ft_putnbr_newline(g_ret);
	else if (ft_strcmp(info[0], "echo") == 0)
		g_ret = (ft_strchr(info[1], '$')) ? ft_print_env_1(info) :
		ft_echo(info, redir, r_flag);
	// else if (ft_strnstr(info[0], "echo", 4))
	// {
	// 	ft_echo(info, redir, r_flag, newline_valid(info));
	// 	g_ret = 0;
	// }
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
		read_env(info, redir, r_flag);
	else if (ft_strcmp(info[0], "exit") == 0)
		exit(0);
	else
		g_ret = ft_ret("command not found\n", 127);
}
