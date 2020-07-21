#include "ft_util.h"

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

int		ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		++i;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_substr(char *str, unsigned start, int len)
{
	char	*ptr;
	int		idx;

	idx = 0;
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (0);
	while (idx < len)
		ptr[idx++] = str[start++];
	ptr[idx] = '\0';
	return (ptr);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_puts(const char *str)
{
	while (*str)
	{
		ft_putchar(*str);
		str++;
	}
}

static size_t	ft_wordcount(char const *s1, char const c)
{
	size_t	count;

	count = 0;
	while (*s1)
	{
		while (*s1 == c)
			s1++;
		if (*s1 && *s1 != c)
			count++;
		while (*s1 && *s1 != c)
			s1++;
	}
	return (count);
}

static size_t	ft_checklen(char const *s1, char const c)
{
	size_t	count;

	count = 0;
	while (*s1 && *s1 != c)
	{
		count++;
		s1++;
	}
	return (count);
}

char			**ft_split(char *s, char c)
{
	char	**result;
	size_t	i;
	size_t	j;

	if (!s || !(result = malloc(sizeof(char *) * (ft_wordcount(s, c) + 1))))
		return (0);
	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			result[i] = malloc(sizeof(char) * (ft_checklen(s, c) + 1));
			if (result[i] == 0)
				return (0);
			j = 0;
			while (*s && *s != c)
				result[i][j++] = *s++;
			result[i][j] = '\0';
			i++;
		}
	}
	result[i] = NULL;
	return (result);
}

char	*ft_strjoin_sh(char const *s1, char const *s2)
{
	size_t	len;
	size_t	i;
	char	*result;

	len = ft_strlen(s1) + ft_strlen(s2);
	result = malloc(sizeof(char) * (len + 2));
	if (result == 0)
		return (0);
	i = 0;
	while (*s1)
		result[i++] = *s1++;
	result[i++] = '/';
	while (*s2)
		result[i++] = *s2++;
	result[i] = '\0';
	return (result);
}

char	*ft_strjoin_newline(char const *s1, char const *s2)
{
	size_t	len;
	size_t	i;
	char	*result;

	len = ft_strlen(s1) + ft_strlen(s2);
	result = malloc(sizeof(char) * (len + 2));
	if (result == 0)
		return (0);
	i = 0;
	while (*s1)
		result[i++] = *s1++;
	result[i++] = '\n';
	while (*s2)
		result[i++] = *s2++;
	result[i] = '\0';
	return (result);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	size_t	i;
	char	*ptr;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!(ptr = (char *)malloc(sizeof(char) * (len1 + len2 + 1))))
		return (NULL);
	i = 0;
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		ptr[len1++] = s2[i++];
	}
	ptr[len1] = '\0';
	return (ptr);
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

int	ft_ret(char *str, int nb)
{
	ft_puts(str);
	return (nb);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (*s1 && *s2 && i < (n - 1))
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - *s2);
		i++;
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - *s2);
}

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		++i;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t i;
	size_t j;

	if (little[0] == 0)
		return ((char *)big);
	i = 0;
	while (big[i] && i < len)
	{
		j = 0;
		while (big[i + j] == little[j] && i + j < len)
		{
			j++;
			if (little[j] == 0)
				return ((char *)big + i);
		}
		i++;
	}
	return (0);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*ptr;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = ft_strlen(s1 + start);
	if (end)
		while (s1[end + start - 1] && ft_strchr(set, s1[end + start - 1]))
			end--;
	if (!(ptr = malloc(sizeof(char) * end + 1)))
		return (0);
	ft_strncpy(ptr, s1 + start, end);
	ptr[end] = '\0';
	return (ptr);
}

void ft_env_free(int i, char **env)
{
	while (i < 0 && env[i])
	{
		i--;
	 	free(env[i]);
	 	env[i] = 0;
	}
	free(env);
	env = 0;
}
