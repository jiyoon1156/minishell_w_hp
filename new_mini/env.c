#include "minishell.h"

int	ft_env_valid(char **info)
{
	info++;
	while (*info)
	{
		if (!ft_strchr(*info, '='))
			return (0);
		info++;
	}
	return (1);
}

int	ft_print_env(char **envp, char **redir, int r_flag)
{
	int		fd;

	fd = redirection(redir, r_flag);
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
	return (0);
}

int	ft_env(char **info, char **envp, char **redir, int r_flag)
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
	while (info[++j])
		env_add(info[j], env);
	i = 0;
	while (env[i])
		i++;
	env[i] = 0;
	ft_print_env(env, redir, r_flag);
	while (--i > 0)
		free(env[i]);
	free(env);
	return (0);
}
