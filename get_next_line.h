/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhur <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 18:00:28 by jhur              #+#    #+#             */
/*   Updated: 2020/06/02 13:51:06 by jhur             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>

char	*ft_strchr(const char *str, int ch);
size_t	ft_strlen(const char *s);
char	*ft_strjoin_gnl(char *s1, char const *s2);
void	*ft_memmove(void *dst, const void *src, size_t len);
char	*ft_strdup(const char *s1);
int		get_next_line(int fd, char **line);

#endif
