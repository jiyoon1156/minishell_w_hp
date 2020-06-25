#include "minishell.h"

int	ft_echo(char **info, char **redir, int r_flag)
{
	int	i;
	int	n_opt;
	int	fd;

	fd = redirection(redir, r_flag);
	i = 1;
	n_opt = 0;
	if ((info[1] && ft_strcmp(info[1], "-n") == 0))
	{
		n_opt = 1;
		i++;
	}
	while (info[i])
	{
		ft_putstr_fd(info[i], fd);
		i++;
		if (info[i])
			ft_putstr_fd(" ", fd);
	}
	if (n_opt == 0)
		ft_putstr_fd("\n", fd);
	return (0);
}
