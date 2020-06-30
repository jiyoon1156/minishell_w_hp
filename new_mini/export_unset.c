#include "minishell.h"

int		ft_unset(char **info, char **envp)
{
	char	**env;
	int		i;
	char	***av;
	int		k;

	av = malloc(sizeof(char **) * ft_cnt(envp));
	i = 0;
	while (envp[i])
	{
		av[i] = ft_split(envp[i], '=');
		i++;
	}
	env = malloc(sizeof(char *) * (i + ft_cnt(info)));
	i = 0;
	k = 0;
	while (envp[k])
	{
		if (ft_strcmp(info[1], av[k][0]) != 0)
			env[i++] = ft_strdup(envp[k]);
		k++;
	}
	env[i] = 0;
	free(g_env);
	g_env = env;
	return (0);
}

void	env_add(char *info, char **env)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strchr(info, '=') - info;
	while (env[i])
	{
		if (!ft_strncmp(env[i], info, len) && env[i][len] == '=')
			break ;
		i++;
	}
	if (env[i])
		free(env[i]);
	env[i] = ft_strdup(info);
}

int		ft_export(char **info, char **envp, int fd)
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
	j = 1;
	while (info[j])
		env_add(info[j++], env);
	i = 0;
	while (env[i])
		i++;
	env[i] = 0;
	//ft_print_env(env, fd);
	free(g_env);
	g_env = env;
	return (0);
}
