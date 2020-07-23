#include "minishell.h"

int	ft_env_valid(char **info)
{
	int	i;

	i = 1;
	while (info && info[i] && (info[i][0] != R_REDIR)
	&& (info[i][0] != L_REDIR))
	{
		if (!ft_strchr(info[i], '='))
			return (127);
		i++;
	}
	return (0);
}

int	ft_print_env(char **envp, int fd)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		ft_putstr_fd(envp[i], fd);
		ft_putstr_fd("\n", fd);
		i++;
	}
	if (fd != 1 && fd != -1)
		close(fd);
	return (0);
}

int	ft_print_env_1(char **info)
{
	int		i;
	char	*ptr;
	char	*str;
	char	**tmp;
	int		len;

	i = -1;
	ptr = ft_strdup(info[1]);
	str = ft_strtrim(ptr, "$");
	free(ptr);
	if (ft_strcmp(str, "?") == 0)
		ft_putnbr_newline(g_ret);
	else
	{
		len = ft_strlen(str);
		while (g_env[++i])
		{
			if (!ft_strncmp(g_env[i], str, len) && g_env[i][len] == '=')
				break ;
		}
		tmp = ft_split(g_env[i], '=');
		ft_puts_newline(tmp[1]);
		ft_free(tmp);
	}
	return (0);
}

int	ft_env(char **info, int fd)
{
	char	**env;
	int		i;
	int		j;

	env = malloc(sizeof(char *) * (ft_cnt(g_env) + ft_cnt(info)));
	i = 0;
	while (g_env[i])
	{
		env[i] = ft_strdup(g_env[i]);
		i++;
	}
	j = 0;
	env[i] = 0;
	while (info[++j] && info[j][0] != R_REDIR && info[j][0] != L_REDIR)
		env_add(info[j], env);
	ft_print_env(env, fd);
	ft_free(env);
	env = 0;
	return (0);
}
