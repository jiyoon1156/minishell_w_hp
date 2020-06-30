#include "minishell.h"

int		ft_slash_cnt(char *line, int flag)
{

}
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
		if (cnt_q % 2 == 0 && *line == '"' && *(line - 1) != '\\')
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
		flag = ft_ret("dquote> ", 1);
	else
		flag = ft_ret("quote> ", 0);
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
