#include "minishell.h"

int	redirection(char *redir, int r_flag)
{
	int	fd;

	fd = 1;
	if (redir != 0)
	{
		if (r_flag == 1)
			fd = open(redir, O_APPEND | O_CREAT | O_WRONLY, S_IRWXU);
		else
			fd = open(redir, O_TRUNC | O_CREAT | O_WRONLY, S_IRWXU);
	}
	if (fd == -1)
		ft_puts("FD ERROR");
	return (fd);
}