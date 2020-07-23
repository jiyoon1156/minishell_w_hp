#include "ft_util.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		++i;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int		ft_cnt(char **envp)
{
	int cnt;

	cnt = 0;
	while (*envp)
	{
		cnt++;
		envp++;
	}
	return (cnt);
}

void	ft_free(char **info)
{
	int i;

	i = 0;
	while (info[i])
		free(info[i++]);
	free(info);
	info = 0;
}
