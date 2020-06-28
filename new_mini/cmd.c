#include "minishell.h"

int		ft_cmd(char **info)
{
	int	i;

	i = 0;
	while (info[i])
	{
		if (ft_strncmp(info[i], ">", ft_strlen(info[i])))
		{

		}
	}
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
	// return (0);
}
/*
void	read_cmd(char **info, char **redir, int r_flag, char **envp)
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
		read_env(info, redir, r_flag);
	else if (ft_strcmp(info[0], "exit") == 0)
		exit(0);
	else
		g_ret = ft_ret("command not found\n", 127);
}*/