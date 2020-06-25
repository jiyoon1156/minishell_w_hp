#ifndef FT_UTIL_H
#define FT_UTIL_H

#include <string.h>
#include "get_next_line.h"
#include <signal.h>
#include <sys/stat.h>
#include <stdio.h>


int		ft_cnt(char **envp);
void	ft_free(char **info);
int		ft_strcmp(const char *s1, const char *s2);
void	ft_putchar(char c);
void	ft_puts(const char *str);
char	**ft_split(char *s, char c);
char	*ft_strjoin_newline(char const *s1, char const *s2);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_putnbr(int n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin_sh(char const *s1, char const *s2);
char	*ft_substr(char *str, unsigned start, int len);
char		*ft_strtrim(char const *s1, char const *set);
char	*ft_strnstr(const char *big, const char *little, size_t len);

#endif