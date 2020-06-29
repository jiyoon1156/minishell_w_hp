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

int		execute_cmd(char *line)
{
	char	**cmd;
	int		idx;
	int		j;

	if (ft_strchr(line, '"') || ft_strchr(line, '\''))
	{
		if ((ft_quote_cnt(line, -1)) != 0)
			line = ft_quote(line);
		ft_quote_cmd(line);
	}
	else
	{
		cmd = ft_split(line, ';');
		idx = 0;
		while (cmd[idx])
		{
			j = 0;
			while (cmd[idx][j] == ' ')
				j++;
			ft_cmd(&cmd[idx++][j]);
		}
	}
	return (0);
}

int		main(int ac, char **av, char **envp)
{
	char	*line;

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
			execute_cmd(line);
			free(line);
			line = 0;
		}
		print_prompt();
	}
	return (0);
}