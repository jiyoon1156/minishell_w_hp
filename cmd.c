#include "minishell.h"

int newline_valid(char **info)
{
	int		echo_newline_flag;
	char	**cmd;

	echo_newline_flag = 0;
	cmd = ft_split(info[0], ' ');
	if ((ft_strcmp(cmd[1], "-n")) == 0)
		echo_newline_flag = 1;
	ft_free(cmd);
	return(echo_newline_flag);
}

int	read_cmd(char **info, char **redir, int r_flag, char **envp)
{
	int new_flag;

	new_flag = 0;
	if (ft_strcmp(info[0], "$?") == 0)
	{
		ft_putnbr(g_ret);
		ft_putchar('\n');
	}
	else if (ft_strcmp(info[0], "echo") == 0)
	{
		if (ft_strchr(info[1], '$'))
			ft_print_env_1(info);
		else
			ft_echo(info, redir, r_flag, new_flag);
		g_ret = 0;
	}
	//else if (ft_strnstr(info[0], "echo", 4)) //////////////////////////
	//{
	//	new_flag = newline_valid(info);
	//	if (new_flag == 1)
	//		ft_echo(info, redir, r_flag, new_flag);
	//	g_ret = 0;
	//}
	else if (ft_strcmp(info[0], "cd") == 0)
		g_ret = ft_cd(info);
	else if (ft_strcmp(info[0], "pwd") == 0)
		g_ret = ft_pwd(info, redir, r_flag);
	else if (ft_strcmp(info[0], "unset") == 0)
	{
		g_ret = 1;
		if (info[1])
		{
			ft_unset(info, envp);
			g_ret = 0;
		}
		else
			ft_puts("unset: not enough arguments\n");
	}
	else if (ft_strcmp(info[0], "export") == 0)
	{
		if (!info[1])
			g_ret = ft_print_env(envp, redir, r_flag);
		if (info[1])
		{
			if ((g_ret = ft_env_valid(info)))
				ft_export(info, envp, redir, r_flag);
		}
	}
	else if (ft_strcmp(info[0], "env") == 0)
	{
		if (!info[1])
			g_ret = ft_print_env(envp, redir, r_flag);
		else
		{
			if ((g_ret = ft_env_valid(info)))
				ft_env(info, envp, redir, r_flag);
			else
				ft_puts("env : no such file or directory\n");
		}
	}
	else if (ft_strcmp(info[0], "exit") == 0)
		exit(0);
	else
	{
		ft_puts("command not found\n");
		g_ret = 127;
	}
	return (g_ret);
}

int	ft_cmd(char *cmd)
{
	char	*ptr;
	char	**redir;
	int		r_flag;
	char	**info;

	redir = 0;
	r_flag = 0;
	if ((ptr = ft_strchr(cmd, '>')))
	{
		if (*(ptr + 1) == '>')
		{
			r_flag = 1;
			if (*(ptr + 2) == '>')
			{
				ft_puts("parse error near '>'\n");
				g_ret = 127;
				return (0);
			}
		}
		redir = ft_split(cmd, '>');
		cmd = redir[0];
	}
	if ((ptr = ft_strchr(cmd, '|')))
	{
		if (*(ptr + 1) == '|')
		{
			ft_puts("parse error near '|'\n");
			g_ret = 127;
			return (0);
		}
		ft_pipe(cmd);
	}
	else
	{
		info = ft_split(cmd, ' ');
		read_cmd(info, redir, r_flag, g_env);
		int i = 0;
		while (info[i])
			free(info[i++]);
		free(info);
	}
	return (0);
}