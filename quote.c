#include "minishell.h"

int ft_quote_cnt(char *line, int flag)
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

	tmp = line;
	while (*line != '"' && *line != '\'')
		line++;
	if (ft_quote_cnt(line, 2) == 2)
	{
		flag = 1;
		ft_puts("dquote> ");
	}
	else
	{
		flag = 0;
		ft_puts("quote> ");
	}
	while (get_next_line(1, &line) > 0)
	{
		tmp = ft_strjoin_newline(tmp, line);
		if (*line != '\0')
		{
			if ((flag = (ft_quote_cnt(line, flag))) == 0)
				return (tmp);
			flag = flag - 1;
		}
		(flag == 1) ? ft_puts("dquote> ") : ft_puts("quote> ");
	}
	return (tmp);
}

int	ft_quote_cmd(char *line)
{
	char	*tmp;
	char	*tmp2;
	char	**info;
	int		cnt;

	tmp = line;
	cnt = 0;
	while (*tmp++)
	{
		if (*tmp == '"' || *tmp == '\'')
			cnt++;
	}
	info = malloc(sizeof(char *) * (cnt + 1));
	int i = 0;
	tmp = line;
	while (*tmp)
	{
		while (*tmp && (*tmp != '"' && *tmp != '\''))
		{
			while (*tmp && *tmp == ' ')//echo 전 띄어쓰기
				tmp++;
			cnt = 0;
			while (*(tmp + cnt) && (*(tmp + cnt) != '"' && *(tmp + cnt) != '\'') && *(tmp + cnt) != ' ')//quote 찾기
				cnt++;
			if (cnt > 0)
				info[i++] = ft_substr(tmp, 0, cnt);
			tmp = tmp + cnt;
		}
		cnt = 0;
		if (*tmp == '"')
		{
			tmp2 = ++tmp;
			while (*tmp++ != '"')
				cnt++;
			info[i++] = ft_substr(tmp2, 0, cnt);
		}
		else if (*tmp == '\'')
		{
			tmp2 = ++tmp;
			while (*tmp++ != '\'')
				cnt++;
			info[i++] = ft_substr(tmp2, 0, cnt);
		}
		while (*tmp && *tmp == ' ')
			tmp++;
	}
	info[i] = 0;
	read_cmd(info, 0, 0, g_env);
	return (0);
}