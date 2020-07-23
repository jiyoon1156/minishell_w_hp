/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 13:51:57 by hpark             #+#    #+#             */
/*   Updated: 2020/07/23 13:51:59 by hpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_quote_cnt(char *line, int flag)
{
	int cnt_dq;
	int cnt_q;

	cnt_dq = 0;
	cnt_q = 0;
	if (flag == 1)
		cnt_dq = 1;
	if (flag == 0)
		cnt_q = 1;
	while (*line)
	{
		if (cnt_q % 2 == 0 && *line == '"')
			cnt_dq++;
		if (cnt_dq % 2 == 0 && *line == '\'')
			cnt_q++;
		line++;
	}
	if (cnt_dq % 2 == 1)
		return (2);
	if (cnt_q % 2 == 1)
		return (1);
	return (0);
}

char	*ft_quote(char *line)
{
	int		flag;
	char	*tmp;
	char	*temp;

	tmp = line;
	while (*line != '"' && *line != '\'')
		line++;
	flag = (ft_quote_cnt(line, 2) == 2) ? ft_ret("dquote> ", 1)
	: ft_ret("quote> ", 0);
	while (get_next_line(1, &line) > 0)
	{
		temp = ft_strjoin_newline(tmp, line);
		free(tmp);
		tmp = temp;
		if (*line != '\0' && (flag = (ft_quote_cnt(line, flag))) == 0)
		{
			free(line);
			return (tmp);
			flag = flag - 1;
		}
		(flag == 1) ? ft_puts("dquote> ") : ft_puts("quote> ");
		free(line);
	}
	return (tmp);
}
