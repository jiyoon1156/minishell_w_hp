#include "minishell.h"

int		quote_check(int *quote, char c)
{
	if (*quote == 0 && (c == '\'' || c == '"'))
		*quote = c;
	else if (*quote != 0 && *quote == c)
		*quote = 0;
	else
		return (0);
	return (1);
}

int		count_char(char *line, int c)
{
	int		i;
	int		cnt;

	i = 0;
	cnt = 0;
	while (line[i])
	{
		if (line[i] == c)
			cnt++;
		i++;
	}
	return (cnt);
}

void	cmds_free(int i, char **cmds)
{
	while (i > 0)
	{
		i--;
		free(cmds[i]);
		cmds[i] = 0;
	}
	free(cmds);
	cmds = 0;
}

char	**get_cmds(char *line, char sep)
{
	char	**cmds;
	char	*tmp;
	int		quote;
	int		i;

	cmds = malloc(sizeof(char *) * (count_char(line, sep) + 2));
	i = 0;
	quote = 0;
	tmp = line;
	while (*line)
	{
		quote_check(&quote, *line);
		if (*line == sep && quote == 0)
		{
			cmds[i++] = ft_substr(tmp, 0, (line++ - tmp));
			while (*line && *line == ' ')
				line++;
			if (*(tmp = line) && *tmp == sep)
			{
				cmds_free(i, cmds);
				ft_putstr_fd("parse error\n", 2);
				return (0);
			}
		}
		line++;
	}
	cmds[i++] = ft_substr(tmp, 0, (line - tmp));
	cmds[i] = 0;
	return (cmds);
}
