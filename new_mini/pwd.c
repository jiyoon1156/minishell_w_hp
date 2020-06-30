#include "minishell.h"

int	ft_pwd(char **info, int fd)
{
	char	path[1024];

	if (info[1] && *info[1] != R_REDIR && *info[1] != L_REDIR)
	{
		ft_puts("too many arguments!");
		ft_puts("\n");
		return (1);
	}
	if (getcwd(path, 1024) == NULL)
	{
		ft_puts("PWD PATH ERROR");
		return (1);
	}
	ft_putstr_fd(path, fd);
	ft_putstr_fd("\n", fd);
	if (fd != -1 && fd != 1)
		close(fd);
	return (0);
}
