#include "minishell.h"

void	ft_echo(char **info, char **redir, int r_flag, int new_flag)
{
	int	i;
	int	n_opt;
	int fd;

	fd = redirection(redir, r_flag);
	(new_flag == 0)? (i = 1) : (i = 0);
	n_opt = 0;
	if ((info[i] && ft_strcmp(info[1], "-n") == 0) || new_flag == 1)
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
}