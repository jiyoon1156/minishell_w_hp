/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhur <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 19:26:09 by jhur              #+#    #+#             */
/*   Updated: 2020/06/02 13:52:29 by jhur             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_free(char **s_res, int ret)
{
	if (*s_res)
	{
		free(s_res);
		s_res = 0;
	}
	return (ret);
}

static int	has_s_res(char **s_res, char **line, char *tmp)
{
	int i;

	if (!(ft_strchr(*s_res, '\n')))
	{
		if (!(*line = ft_strjoin_gnl(*line, *s_res)))
			ft_free(s_res, -1);
		free(*s_res);
		*s_res = NULL;
	}
	else
	{
		i = 0;
		while ((*s_res)[i] != '\n' && (*s_res)[i] != '\0')
		{
			tmp[i] = (*s_res)[i];
			i++;
		}
		tmp[i] = '\0';
		if (!(*line = ft_strjoin_gnl(*line, tmp)))
			ft_free(s_res, -1);
		ft_memmove(*s_res, *s_res + i + 1, ft_strlen(*s_res) - i);
		return (1);
	}
	return (0);
}

static int	has_newline(char *buf, char *tmp, char **s_res, char **line)
{
	int i;

	if (ft_strchr(buf, '\n'))
	{
		i = -1;
		while (buf[++i] != '\n')
			tmp[i] = buf[i];
		tmp[i] = '\0';
		if (!(*line = ft_strjoin_gnl(*line, tmp)))
			ft_free(s_res, -1);
		free(*s_res);
		*s_res = NULL;
		if (!(*s_res = ft_strdup(&buf[i + 1])))
			ft_free(s_res, -1);
		return (1);
	}
	return (0);
}

int			get_next_line(int fd, char **line)
{
	size_t		res;
	char		buf[BUFFER_SIZE + 1];
	char		tmp[BUFFER_SIZE + 1];
	static char	*s_res;

	if (fd < 0 || line == NULL || (read(fd, buf, 0) < 0) || BUFFER_SIZE < 1)
		return (-1);
	*line = ft_strdup("");
	if (s_res)
	{
		if (has_s_res(&s_res, line, tmp) == 1)
			return (1);
	}
	while ((res = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[res] = '\0';
		if (has_newline(buf, tmp, &s_res, line) == 1)
			return (1);
		if (!(*line = ft_strjoin_gnl(*line, buf)))
			ft_free(&s_res, -1);
	}
	return (res);
}
