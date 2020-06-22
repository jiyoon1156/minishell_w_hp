#include "get_next_line.h"
//#include "command.h"
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>

#define PTH "./minishell"

#define	LF 10 // \n

int	g_ret = 0;
char	**g_env = 0;

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int n)
{
	long	nb;
	nb = n;
	if (nb < 0)
	{
		ft_putchar('-');
		nb *= -1;
	}
	if (nb >= 10)
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
	else
		ft_putchar(nb + '0');
}

int		ft_strcmp(const char *s1, const char *s2)
{
	int	i;
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		++i;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	ft_puts(const char *str)
{
	while (*str)
	{
		ft_putchar(*str);
		str++;
	}
}
static size_t	ft_wordcount(char const *s1, char const c)
{
	size_t	count;
	count = 0;
	while (*s1)
	{
		while (*s1 == c)
			s1++;
		if (*s1 && *s1 != c)
			count++;
		while (*s1 && *s1 != c)
			s1++;
	}
	return (count);
}
static size_t	ft_checklen(char const *s1, char const c)
{
	size_t	count;
	count = 0;
	while (*s1 && *s1 != c)
	{
		count++;
		s1++;
	}
	return (count);
}
char			**ft_split(char *s, char c)
{
	char	**result;
	size_t	i;
	size_t	j;
	if (!s || !(result = malloc(sizeof(char *) * (ft_wordcount(s, c) + 1))))
		return (0);
	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			result[i] = malloc(sizeof(char) * (ft_checklen(s, c) + 1));
			if (result[i] == 0)
				return (0);
			j = 0;
			while (*s && *s != c)
				result[i][j++] = *s++;
			result[i][j] = '\0';
			i++;
		}
	}
	result[i] = NULL;
	return (result);
}
char	*ft_strjoin_sh(char const *s1, char const *s2)
{
	size_t	len;
	size_t	i;
	char	*result;
	len = ft_strlen(s1) + ft_strlen(s2);
	result = malloc(sizeof(char) * (len + 2));
	if (result == 0)
		return (0);
	i = 0;
	while (*s1)
		result[i++] = *s1++;
	result[i++] = '/';
	while (*s2)
		result[i++] = *s2++;
	result[i] = '\0';
	return (result);
}

char	*ft_strjoin_newline(char const *s1, char const *s2)
{
	size_t	len;
	size_t	i;
	char	*result;
	len = ft_strlen(s1) + ft_strlen(s2);
	result = malloc(sizeof(char) * (len + 2));
	if (result == 0)
		return (0);
	i = 0;
	while (*s1)
		result[i++] = *s1++;
	result[i++] = '\n';
	while (*s2)
		result[i++] = *s2++;
	result[i] = '\0';
	return (result);
}
void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

int		redirection(char **redir, int r_flag)
{
	int	fd;
	fd = 1;
	if (redir != 0)
	{
		while (*redir[1] == ' ')
			redir[1]++;
		if (r_flag == 1)
			fd = open(redir[1], O_APPEND | O_CREAT | O_WRONLY, S_IRWXU);
		else
			fd = open(redir[1], O_TRUNC | O_CREAT | O_WRONLY, S_IRWXU);
	}
	if (fd == -1)
		ft_puts("FD ERROR");
	return (fd);
}
void	print_prompt()
{
	ft_puts("minish% ");
}
void	ft_echo(char **info, char **redir, int r_flag)
{
	int	i;
	int	n_opt;
	int fd;

	fd = redirection(redir, r_flag);
	i = 1;
	n_opt = 0;
	if (info[i] && ft_strcmp(info[1], "-n") == 0)
	{
		n_opt = 1;
		i++;
	}
	while (info[i])
	{
		ft_putstr_fd(info[i], fd);
		i++;
		if (info[i])
			ft_putstr_fd(" ", fd);
	}
	if (n_opt == 0)
		ft_putstr_fd("\n", fd);
}
int	ft_pwd(char **info, char **redir, int r_flag)
{
	char	path[1024];
	int		fd;
	//char *argv[] = {"./minishell", NULL};
	//char *envp[] = {NULL};
	if (info[1] != NULL)
	{
		ft_puts("too many arguments!");
		return (1);
	}
	if ((fd = redirection(redir, r_flag)) == -1)
		return (1);
	if (getcwd(path, 1024) == NULL)
	{
		ft_putstr_fd("PWD PATH ERROR", fd);
		return (1);
	}
	ft_putstr_fd(path, fd);
	ft_putstr_fd("\n", fd);
	if (fd != -1 && fd != 1)
		close(fd);
	//execve("./minishell", argv, envp);
	return (0);
}
void	ft_cd(char **info)
{
	int res;
	res = chdir(info[1]);
	(res == 0)? : ft_puts("cd: no such file or directory\n");
}
void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_puts("SIGINT");
		exit(0);
	}
	if (sig == SIGQUIT)
		ft_puts("SIGQUIT");
}
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
	int flag;
	char *tmp;
	tmp = line;
	while (*line != '"' && *line != '\'')
		line++;
	if (*line == '"')
	{
		flag = 1;
		ft_puts("dquote> ");
	}
	if (*line == '\'')
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
		(flag == 1)? ft_puts("dquote> ") : ft_puts("quote> ");
	}
	return (tmp);
}
void	ft_unset(char **info, char **envp)
{
	char	**env;
	int i = 0;
	int j = 1;
	char	***av;

	while(info[j])
		j++;
	while (envp[i])
		i++;
	av = malloc(sizeof(char **) * i);
	i = 0;
	while (envp[i])
	{
		av[i] = ft_split(envp[i], '=');
		i++;
	}
	env = malloc(sizeof(char *) * (i - j + 2));
	i = 0;
	int k = 0;
	while (envp[k])
	{
		if (ft_strcmp(info[1], av[k][0]) != 0)
		{
			env[i++] = ft_strdup(envp[k]);
		}
		k++;
	}
	env[i] = 0;
	free(g_env);
	g_env = env;
}
int		ft_env_valid(char **info)
{
	info++;
	while (*info)
	{
		if (!ft_strchr(*info, '='))
			return (0);
		info++;
	}
	return (1);
}
void	ft_print_env(char **envp, char **redir, int r_flag)
{
	int fd;
	fd = redirection(redir, r_flag);
	while (*envp)
	{
		ft_putstr_fd(*envp, fd);
		ft_putstr_fd("\n", fd);
		envp++;
	}
	if (fd != 1 && fd != -1)
		close(fd);
}
int		ft_cnt(char **envp)
{
	int cnt;
	cnt = 0;
	while (*envp)
	{
		cnt++;
		envp++;
	}
	return (cnt);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

void env_add(char *info, char **env)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strchr(info, '=') - info;
	while (env[i])
	{
		if (!ft_strncmp(env[i], info, len) && env[i][len] == '=')
			break ;
		i++;
	}
	if (env[i])
		free(env[i]);
	env[i] = ft_strdup(info);
}
#include <stdio.h>
void	ft_env(char **info, char **envp, char **redir, int r_flag)
{
	char **env;
	int i;
	int j;

	env = malloc(sizeof(char *) * (ft_cnt(envp) + ft_cnt(info) + 1));
	i = 0;
	while (envp[i])
	{
		env[i] = ft_strdup(envp[i]);
		i++;
	}
	j = 1;
	while (info[j])
	{
		env_add(info[j], env);
		j++;
	}
	while (env[i])
		i++;
	env[i] = 0;
	ft_print_env(env, redir, r_flag);
	while (--i >= 0)
		free(env[i]);
	free(env);
}

void	ft_export(char **info, char **envp, char **redir, int r_flag)
{
	char **env;
	int i;
	int j;

	env = malloc(sizeof(char *) * (ft_cnt(envp) + ft_cnt(info) + 1));
	i = 0;
	while (envp[i])
	{
		env[i] = ft_strdup(envp[i]);
		i++;
	}
	j = 1;
	while (info[j])
	{
		env_add(info[j], env);
		j++;
	}
	while (env[i])
		i++;
	env[i] = 0;
	ft_print_env(env, redir, r_flag);
	free(g_env);
	g_env = env;	
}

int	read_cmd(char **info, char **redir, int r_flag, char **envp)
{
	int res = 0;

	if (ft_strcmp(info[0], "$?") == 0)
		ft_putnbr(g_ret);
	else if (ft_strcmp(info[0], "echo") == 0)
		ft_echo(info, redir, r_flag);
	else if (ft_strcmp(info[0], "cd") == 0)
		ft_cd(info);
	else if (ft_strcmp(info[0], "pwd") == 0)
		g_ret = ft_pwd(info, redir, r_flag);
	else if (ft_strcmp(info[0], "export") == 0)
	{
		if (ft_env_valid(info))
			ft_export(info, envp, redir, r_flag);
	}
	else if (ft_strcmp(info[0], "unset") == 0)
	{
		if (info[1])
			ft_unset(info, envp);
	}
	else if (ft_strcmp(info[0], "env") == 0)
	{
		if (!info[1])
			ft_print_env(envp, redir, r_flag);
		if (info[1])
		{
			if (ft_env_valid(info))
				ft_env(info, envp, redir, r_flag);
			else
				ft_puts("env : no such file or directory\n");
		}
	}
	else if (ft_strcmp(info[0], "exit") == 0)
		exit(0);
	else
		g_ret = 127;
	
	return (g_ret);
}

char **ft_cpenv(char **envp)
{
	char **env;
	int i;
	
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

char	**ft_find_path()
{
	int		i;
	char	**path;

	i = 0;
	while (g_env[i])
	{
		if (ft_strncmp(g_env[i], "PATH=", 5) == 0)
		{
			path = ft_split(&g_env[i][5], ':');
			return (path);
		}
		i++;
	}
}
#include <dirent.h>
char *ft_pathjoin(char **path, char **cmd)
{
	DIR *dp = NULL;
	struct dirent *entry = NULL;
	struct stat buf;
	char *res;

	int i = 0;
	while (path[i])
	{
		if ((dp = opendir(path[i])) == NULL)
		{
			i++;
			continue;
		}
		while ((entry = readdir(dp)) != NULL)
		{
			lstat(entry->d_name, &buf);
			if (S_ISDIR(buf.st_mode))
			{
				if((ft_strcmp(entry->d_name, cmd[0]) == 0))
				{
					res = ft_strjoin_sh(path[i], cmd[0]);
					break;
				}
			}
		}
		closedir(dp);
		i++;
	}
	return (res);
}

void child_process(char **info, int *pipefd, char *path_cmd)
{
	if(pipefd[0] != 0)
		close(pipefd[0]);
	dup2(pipefd[1],1);
	if(pipefd[1] != 1)
		close(pipefd[1]);
	execve(path_cmd, info, g_env);
	// execvp(info[0], info);
	exit(0);
}

void parent_process(char **path, int *pipefd, int i, char **cmd)
{
	int childpid2;
	char **info;
	char *path_cmd;
	int status;
	int pipefd2[2];

	i++;
	//if (cmd[i + 1])
	//	dup2(pipefd[1], 1);
	close(pipefd[1]); //EOF
	dup2(pipefd[0], 0);
	close(pipefd[0]);
	pipefd2[0] = 0;
	pipefd2[1] = 1;
	if (cmd[i + 1])
		pipe(pipefd2);
	childpid2 = fork();
	if (childpid2 == -1)
	{
		perror("fork failed");
		exit(1);
	}
	else if (childpid2 == 0)
	{
		info = ft_split(cmd[i], ' ');
		path_cmd = ft_pathjoin(path, info);
		child_process(info, pipefd2, path_cmd);
	}
	else
	{
		//execvp("grep",cmd2);
		waitpid(childpid2, &status, 0);
		if (cmd[i + 1])
		{
			parent_process(path, pipefd2, i, cmd);
		}
	}
}


void ft_pipe(char *cm, char **redir, int r_flag)
{
	int pipefd[2];
	int childpid,childpid2;
	char* cmd3[3]={"ls",NULL,NULL};
	char* cmd2[3]={"grep",".c", NULL};
	char **cmd;
	int status;
	char **path = ft_find_path();

	cmd = ft_split(cm, '|');
	char **info;// = ft_split(cmd[0], ' ');
	char *path_cmd;
	//path_cmd = ft_pathjoin(path, info[0]);
	//
	//while cmd 숫자만큼
	//
	int i = 0;
	pipe(pipefd);

	childpid = fork();
	if (childpid == -1)
	{
		perror("fork failed");
		exit(1);
	}
	else if (childpid == 0)
	{
		info = ft_split(cmd[i], ' ');
		path_cmd = ft_pathjoin(path, info);
		child_process(info, pipefd, path_cmd);
		//child
		//close(pipefd[0]);
		//dup2(pipefd[1],1);
		//close(pipefd[1]);
		//execve(path_cmd, info, g_env);
		//// execvp(info[0], info);
		//exit(0);
	}
	else
	{
		waitpid(childpid2, &status, 0);
		//parent
		//i++;
		//if (cmd[i + 1])
		//	dup2(pipefd[1], 1);
		//close(pipefd[1]); //EOF
		//dup2(pipefd[0], 0);
		//close(pipefd[0]);
		//childpid2 = fork();
		//if (childpid2 == -1)
		//{
		//	perror("fork failed");
		//	exit(1);
		//}
		//else if (childpid2 == 0)
		//{
		//	info = ft_split(cmd[i], ' ');
		//	path_cmd = ft_pathjoin(path, info);
		//	child_process(info, pipefd, path_cmd);
		//}
		//else
		//{
		//	//execvp("grep",cmd2);
		//	waitpid(childpid2, &status, 0);
		//}
		parent_process(path, pipefd, i, cmd);
	}
	
	//return (0);
}

int	ft_cmd(char *cmd)
{
	char	*ptr;
	char	**redir;
	int		r_flag;
	char	**info;

	redir = 0;
	r_flag = 0;
	if ((ptr = ft_strchr(cmd, '>')))
	{
		if (*(ptr + 1) == '>')
		{
			r_flag = 1;
			if (*(ptr + 2) == '>')
				ft_puts("ERROR");
		}
		redir = ft_split(cmd, '>');
		cmd = redir[0];
	}
	if (ft_strchr(cmd, '|'))
	{
		dup2(0, 3);
		dup2(1, 4);
		ft_pipe(cmd, redir, r_flag);
		dup2(3, 0);
		dup2(4, 1);
	}
	else
	{
		info = ft_split(cmd, ' ');
		read_cmd(info, redir, r_flag, g_env);
	int i = 0;
	while (info[i])
		free(info[i++]);
	free(info);
	}
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	i;
	size_t	s_len;

	s_len = ft_strlen(s);
	result = malloc(sizeof(char) * (len + 1));
	if (result == 0)
		return (0);
	i = 0;
	while (i < len && start < s_len)
	{
		result[i] = s[i + start];
		i++;
	}
	result[i] = '\0';
	return (result);
}

int	ft_quote_cmd(char *line)
{
	char *tmp;
	char *tmp2;
	char **info;
	int	cnt;

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
		while (*tmp && *tmp == ' ')
			tmp++;
		cnt = 0;
		while (*tmp && (*tmp != '"' && *tmp != '\''))
		{
			tmp++;
			cnt++;
		}
		if (cnt != 0)
			info[i++] = ft_substr((tmp - cnt), 0, cnt - 1);
		while (*tmp && *tmp == ' ')
			tmp++;
		cnt = 0;	
		if (*tmp == '"')
		{
			tmp++;
			while (*tmp++ != '"')
				cnt++;
			info[i++] = ft_substr((tmp - cnt - 1), 0, cnt);
		}
		else if (*tmp == '\'')
		{
			tmp++;
			while (*tmp++ != '\'')
				cnt++;
			info[i++] = ft_substr((tmp - cnt - 1), 0, cnt);
		}
		while (*tmp && *tmp == ' ')
			tmp++;
	}
	info[i] = 0;
	i = -1;
	while(info[++i])
		printf("info[%d] = %s\n", i, info[i]);
	read_cmd(info, 0, 0, g_env);
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	char	**info;
	char	*ptr;
	//char	**redir;
	//int		r_flag;
	int flag_echo;
	char	**info_env;
	pid_t	pid;
	int		res;

	g_env = ft_cpenv(envp);
	//redir = 0;
	//r_flag = 0;
	signal(SIGINT, signal_handler); //ctrl+c
	signal(SIGQUIT, signal_handler);//ctrl+backslash

		print_prompt();
		while (get_next_line(1, &line) > 0)
		{
			if (*line != '\0')
			{
				if (ft_strchr(line, '"') || ft_strchr(line, '\''))
				{
					if ((ft_quote_cnt(line, -1)) != 0)
					{
				//		if (ft_strcmp(line, "echo"))
				//			flag_echo = 1;

						line = ft_quote(line);
					}
					ft_quote_cmd(line);
				//		info = ft_split(line, '"');
					
				//		if (flag_echo == 1)
				//			ft_puts(info[1]);
				//		else
				//			ft_puts(info[0]);
				//		ft_puts("\n");
				//	} //ft_puts(line);
				//	else //((ft_quote_cnt(line, -1)) == 0)
				//	{
				//		//ft_puts("hi");
				//		info = ft_split(line, ' ');
				//		int i = 1;
				//		while (info[i])
				//		{
				//			int j = 0;
				//			while(j < (ft_strlen(info[i]) - 2))
				//			{
				//				ft_putchar(info[i][j + 1]);
				//				j++;
				//			}
				//			i++;
				//			ft_puts(" ");
				//		}
				//		ft_puts("\n");
				//	}
				//	//ft_quote_cmd(line);
				}
				else
				{if (ft_strchr(line, ';'))
				{
					char **cmd = ft_split(line, ';');
					int idx;
					idx = 0;
					while (cmd[idx])
					{
						int j = 0;
						while (cmd[idx][j] == ' ')
							j++;
						ft_cmd(&cmd[idx++][j]);
					}
				}
				else
					ft_cmd(line);
				}
				free(line);
				line = 0;
			}

			print_prompt();
		}
	// _exit(EXIT_SUCCESS);
	//}
	//else
	//{
    //    int status;
	//	ft_puts("parent?");
	//	print_prompt();
    //    (void)waitpid(pid, &status, 0);
	//	//printf("pid last:%d\n", pid);
	//}
	return (0);
}