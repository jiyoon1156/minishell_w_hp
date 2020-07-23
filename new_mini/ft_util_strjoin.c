#include "ft_util.h"

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
