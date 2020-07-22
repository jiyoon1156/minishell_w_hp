#include "minishell.h"

void	ft_free_3(char ***info)
{
	int i;

	i = 0;
	while (info[i])
		ft_free(info[i++]);
	free(info);
	info = 0;
}

int		ft_unset(char **info, char **envp)
{
	char	**env;
	int		i;
	char	***av;
	int		k;

	av = malloc(sizeof(char **) * (ft_cnt(envp) + 1));
	i = 0;
	while (envp[i])
	{
		av[i] = ft_split(envp[i], '=');
		i++;
	}
	av[i] = 0;
	env = malloc(sizeof(char *) * (i + ft_cnt(info)));
	i = 0;
	k = 0;
	while (envp[k])
	{
		if (ft_strcmp(info[1], av[k][0]) != 0)
			env[i++] = ft_strdup(envp[k]);
		k++;
	}
<<<<<<< HEAD
	// env[i] = 0;
	free(g_env);
	//ft_env_free(i, g_env);
=======
	env[i] = 0;
	ft_free(g_env);
>>>>>>> 2c7ef0837d503c76487ee08bd603f6a9933df8bd
	g_env = env;
	ft_free_3(av);
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
<<<<<<< HEAD
	// if (env[i])
	// 	free(env[i]);
=======
	if (env[i])
		free(env[i]);
	if (env[i] == 0)
		env[i + 1] = 0;
>>>>>>> 2c7ef0837d503c76487ee08bd603f6a9933df8bd
	env[i] = ft_strdup(info);
}

int		ft_export(char **info, char **envp, int fd)
{
	char	**env;
	int		i;
	int		j;

	if (!ft_env_valid(info))
	{
		ft_puts("bad assignment\n");
		return (1);
	}
	env = malloc(sizeof(char *) * (ft_cnt(envp) + ft_cnt(info) + 1));
	i = 0;
	while (envp[i])
	{
		env[i] = ft_strdup(envp[i]);
		i++;
	}
	env[i] = 0;
	j = 1;
	while (info[j])
		env_add(info[j++], env);
<<<<<<< HEAD
	while (env[i])
		i++;
	env[i] = 0;
	//ft_print_env(env, fd);
	free(g_env);
=======
	i = 0;
	// while (env[i])
	// 	i++;
	// env[i] = 0;
	ft_free(g_env);
>>>>>>> 2c7ef0837d503c76487ee08bd603f6a9933df8bd
	g_env = env;
	return (0);
}
