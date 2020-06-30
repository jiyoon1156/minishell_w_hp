#include "minishell.h"

int	ft_env_valid(char **info)
{
	info++;
	while (*info && (*info[0] != R_REDIR) && (*info[0] != L_REDIR))
	{
		if (!ft_strchr(*info, '='))
			return (0);
		info++;
	}
	return (1);
}

int	ft_print_env(char **envp, int fd)
{
	while (*envp)
	{
		ft_putstr_fd(*envp, fd);
		ft_putstr_fd("\n", fd);
		envp++;
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

	i = 0;
	ptr = ft_strdup(info[1]);
	str = ft_strtrim(ptr, "$");
	free(ptr);
	if (ft_strcmp(str, "?") == 0)
		ft_putnbr_newline(g_ret);
	else
	{
		len = ft_strlen(str);
		while (g_env[i])
		{
			if (!ft_strncmp(g_env[i], str, len) && g_env[i][len] == '=')
				break ;
			i++;
		}
		tmp = ft_split(g_env[i], '=');
		ft_puts(tmp[1]);
		ft_free(tmp);
		ft_puts("\n");
	}
	return (0);
}

int	ft_env(char **info, char **envp, int fd)
{
	char	**env;
	int		i;
	int		j;

	env = malloc(sizeof(char *) * (ft_cnt(envp) + ft_cnt(info) + 1));
	i = 0;
	while (envp[i])
	{
		env[i] = ft_strdup(envp[i]);
		i++;
	}
	j = 0;
	while (info[++j] && info[j][0] != R_REDIR && info[j][0] != L_REDIR)
		env_add(info[j], env);
	i = 0;
	while (env[i])
		i++;
	env[i] = 0;
	ft_print_env(env, fd);
	while (i < 0 && env[i])
	{
		i--;
	 	free(env[i]);
	 	env[i] = 0;
	}
	free(env);
	env = 0;
	return (0);
}
