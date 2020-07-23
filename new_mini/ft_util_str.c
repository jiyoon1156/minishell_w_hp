#include "ft_util.h"

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

int		ft_strncmp(const char *s1, const char *s2, size_t n)
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

char	*ft_strtrim(char const *s1, char const *set)
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
