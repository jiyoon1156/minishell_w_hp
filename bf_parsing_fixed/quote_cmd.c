#include "minishell.h"

int		end_of_quote(char *tmp)
{
	int		cnt;

	cnt = 0;
	if (*(tmp - 1) == '"')
	{
		while (*tmp++ != '"')
			cnt++;
	}
	else if (*(tmp - 1) == '\'')
	{
		while (*tmp++ != '\'')
			cnt++;
	}
	return (cnt);
}

int		cnt_info(char *line)
{
	char	*tmp;
	int		cnt;

	tmp = line;
	cnt = 0;
	while (*tmp++)
	{
		if (*tmp == '"' || *tmp == '\'' || *tmp == ' ')
			cnt++;
	}
	return (cnt);
}

int		until_quote(char *tmp)
{
	int	cnt;

	cnt = 0;
	while (*(tmp + cnt))
	{
		if (*(tmp + cnt) != '"' && *(tmp + cnt) != '\'' && *(tmp + cnt) != ' ')
			cnt++;
		else
			break ;
	}
	return (cnt);
}

char	**get_info(char *tmp, char **info)
{
	int		cnt;
	int		i;

	i = 0;
	while (*tmp)
	{
		while (*tmp && (*tmp != '"' && *tmp != '\''))
		{
			while (*tmp && *tmp == ' ')
				tmp++;
			cnt = until_quote(tmp);
			if (cnt > 0)
				info[i++] = ft_substr(tmp, 0, cnt);
			tmp += cnt;
		}
		if (*tmp++)
		{
			cnt = end_of_quote(tmp);
			info[i++] = ft_substr(tmp, 0, cnt);
			tmp += cnt + 1;
		}
	}
	info[i] = 0;
	return (info);
}

int		ft_quote_cmd(char *line)
{
	char	**info;

	info = malloc(sizeof(char *) * (cnt_info(line) + 1));
	info = get_info(line, info);
	read_cmd(info, 0, 0, g_env);
	return (0);
}
