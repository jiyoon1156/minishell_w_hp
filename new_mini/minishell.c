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
		exit(1);
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
			if (*(tmp = line) == sep)//; 가 두개일때 파스에러
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
	char	**cmd;
	char	**info;
	int		i;
	int		j;

	if (!(cmd = get_cmds(cmds, '|')))
		return (0);
	i = 0;
	while (cmd[i])
	{

		info = get_info(cmd[i++]);
		//read_cmd(info);	/* redirection, pipe 처리도 같이 */
		//ft_cmd(&cmds[idx++][j]);
	}
	ft_cmd(info);
	return (0);
}

int		main(int ac, char **av, char **envp)
{
	char	*line;
	char	**cmds;

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
				while (*cmds)
					execute_cmds(*cmds++);
			}
			free(line);
			line = 0;
		}
		print_prompt();
	}
	return (0);
}