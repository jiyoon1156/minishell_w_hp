#include "minishell.h"

int	ft_echo(char **info, int fd)
{
	int	i;
	int	n_opt;

	n_opt = 0;
	i = 1;
	if ((info[1] && ft_strcmp(info[1], "-n") == 0))
	{
		n_opt = 1;
		i++;
	}
	while (info[i])
	{
		if (*info[i] == R_REDIR || *info[i] == L_REDIR)
			break ;
		ft_putstr_fd(info[i], fd);
		i++;
		if (info[i])
			ft_putstr_fd(" ", fd);
	}
	if (n_opt == 0)
		ft_putstr_fd("\n", fd);
	return (0);
}
