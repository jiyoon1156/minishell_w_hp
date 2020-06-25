#include "minishell.h"

char **ft_find_home()
{
	int		i;
	char	**path;
	char	**home;

	i = 0;
	while(g_env[i])
	{
		if((ft_strncmp(g_env[i], "HOME=", 5) == 0))
		{
			path = ft_split(g_env[i], '=');
		}
		i++;
	}
	home = path;
	ft_free(path);
	return(home);
}

int	ft_cd(char **info)
{
	int		res;
	char	**home;

	home = ft_find_home();
	if(info[1])
		res = chdir(info[1]);
	else
		res = chdir(home[1]);
	if (res != 0)
	{
		res = 1;
		ft_puts("cd: no such file or directory\n");
	}
	return (res);
}