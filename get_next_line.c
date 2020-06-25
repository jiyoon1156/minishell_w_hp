/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpark <hpark@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 20:18:05 by hpark             #+#    #+#             */
/*   Updated: 2020/06/06 15:32:48 by hpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_free(char **p, int ret)
{
	if (*p && ret != 1)
	{
		free(*p);
		*p = 0;
	}
	return (ret);
}

int	join_line_and_src(char *src, char **line)
{
	char	*tmp;

	tmp = *line;
	if (!(*line = ft_strjoin(*line, src)))
		return (ft_free(&tmp, -1));
	free(tmp);
	tmp = 0;
	ft_bzero(src, ft_strlen(src));
	return (0);
}

int	fill_line(char *src, char **line)
{
	char	*tmp;
	int		i;

	if (src == 0)
		return (0);
	if ((tmp = ft_strchr(src, '\n')) != 0)
	{
		*tmp = '\0';
		if (join_line_and_src(src, line) == -1)
			return (-1);
		i = 0;
		while (*(++tmp) != '\0')
		{
			src[i++] = *tmp;
			*tmp = '\0';
		}
		return (1);
	}
	else
	{
		if (join_line_and_src(src, line) == -1)
			return (-1);
	}
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char	*rest;
	char		buff[BUFFER_SIZE + 1];
	int			ret;
	int			ret2;

	if (BUFFER_SIZE < 1 || line == NULL || fd < 0 || read(fd, buff, 0) < 0)
		return (-1);
	if (!(*line = ft_strdup("")))
		return (-1);
	if ((ret = (fill_line(rest, line))) != 0)
		return (ret);
	while ((ret = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[ret] = '\0';
		if ((ret2 = fill_line(buff, line)) == 1)
		{
			if (ft_free(&rest, 0) == 0 && !(rest = ft_strdup(buff)))
				return (-1);
			ft_bzero(buff, BUFFER_SIZE);
			return (1);
		}
		else if (ret2 == -1)
			return (ret2);
	}
	return (ft_free(&rest, ret));
}


//#include <stdio.h>
//#include <fcntl.h>

//int main()
//{

//	int fd = open("as.txt", O_RDONLY);
//	int ret = 0;
//	char *line;

//	//while ((ret = get_next_line(fd, &line)) > 0)
//	//{
//	//	printf("%s\n", line);
//	//	free(line);
//	//	line = 0;
//	//}
//	ret = get_next_line(fd, &line);
//	printf("ret is %d\n%s\n",ret, line);
//	free(line);
//	line = 0;

//	ret = get_next_line(fd, &line);
//	printf("ret is %d\n%s\n",ret, line);
//	free(line);
//	line = 0;
//}