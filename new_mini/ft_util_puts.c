#include "ft_util.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

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

void	ft_putnbr(int n)
{
	long	nb;

	nb = n;
	if (nb < 0)
	{
		ft_putchar('-');
		nb *= -1;
	}
	if (nb >= 10)
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
	else
		ft_putchar(nb + '0');
}

void	ft_putnbr_newline(int n)
{
	ft_putnbr(n);
	ft_puts("\n");
}

int		ft_ret(char *str, int nb)
{
	ft_putstr_fd(str, 2);
	return (nb);
}
