#include "minishell.h"

int	ft_pwd(char **info, char **redir, int r_flag)
{
	char	path[1024];
	int		fd;

	if (info[1] != NULL)
	{
		ft_puts("too many arguments!\n");
		return (1);
	}
	if ((fd = redirection(redir, r_flag)) == -1)
		return (1);
	if (getcwd(path, 1024) == NULL)
	{
		ft_puts("PWD PATH ERROR\n");
		return (1);
	}
	ft_putstr_fd(path, fd);
	ft_putstr_fd("\n", fd);
	if (fd != -1 && fd != 1)
		close(fd);
	return (0);
}