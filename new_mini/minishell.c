#include "minishell.h"

int	g_ret = 0;
char **g_env = 0;

void	print_prompt(void)
{
	ft_puts("minish% ");
}

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_puts("SIGINT");
		// exit(1);
		ft_puts("minish% ");
	}
	if (sig == SIGQUIT)
		ft_puts("SIGQUIT");
}

char	**ft_cpenv(char **envp)
{
	char	**env;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	env = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (envp[i])
	{
		env[i] = ft_strdup(envp[i]);
		i++;
	}
	return (env);
}

int	quote_check(int *quote, char c)
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

/* ;를 기준으로 commands 끊기
		따옴표 고려해서 */

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
			if (*(tmp = line) && *tmp == sep)//; 가 두개일때 파스에러
			{
				//에러 처리하기 - free하고
				ft_puts("parse error\n");
				return (0);
			}
		}
		line++;
	}
	cmds[i++] = ft_substr(tmp, 0, (line - tmp));
	cmds[i] = 0;
	return (cmds);
}

int		execute_cmds(char *cmds)
{
	//char	**cmd;
	char	**info;
	int		i;
	int		j;

	i = 0;

	if (ft_strchr(cmds, '|'))
		ft_pipe(cmds);
	else
	{
		info = get_info(cmds);
		ft_cmd(info);
		ft_free(info);
	}
	//ft_free(info);
	// while (*info)
	// {
	// 	free(*info);
	// 	*info = 0;
	// 	info++;
	// }
	// free(info);
	// info = 0;
	return (0);
}

int		main(int ac, char **av, char **envp)
{
	char	*line;
	char	**cmds;
	int		i;

	(void)ac;
	(void)av;
	g_env = ft_cpenv(envp);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	print_prompt();
	while (get_next_line(1, &line) > 0)
	{
		if (*line != '\0')
		{
			if ((ft_quote_cnt(line, -1)) != 0)
				line = ft_quote(line);
			if ((cmds = get_cmds(line, ';')))
			{
				i = 0;
				while (cmds[i])
				{
					execute_cmds(cmds[i]);
					// free(cmds[i]);
					// cmds[i] = 0;
					i++;
				}
				ft_free(cmds);
				// free(cmds);
				// cmds = 0;
			}
			free(line);
			line = 0;
		}
		print_prompt();
	}
	return (0);
}