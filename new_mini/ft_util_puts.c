#include "ft_util.h"

void	ft_puts_newline(const char *str)
{
	while (*str)
	{
		write(1, str, 1);
		str++;
	}
	write(1, "\n", 1);
}

void	ft_puts(const char *str)
{
	while (*str)
	{
		write(1, str, 1);
		str++;
	}
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

int		ft_ret(char *str, int nb)
{
	ft_putstr_fd(str, 2);
	return (nb);
}
