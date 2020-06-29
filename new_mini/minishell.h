#ifndef MINISHELL_H
# define MINISHELL_H

# include "ft_util.h"
# include "get_next_line.h"
# include <sys/wait.h>
# include <dirent.h>

extern int g_ret;
extern char **g_env;

char	**get_info(char *line);
int		count_char(char *line, int c);
int		quote_check(int *quote, char c);
int		redirection(char *redir, int r_flag);
int		ft_echo(char **info, int fd);
int		ft_pwd(char **info, int fd);
int		ft_cd(char **info);
int		ft_unset(char **info, char **envp);
int		ft_env(char **info, char **envp, int fd);
int		ft_env_valid(char **info);
int		ft_print_env(char **envp, int fd);
int		ft_print_env_1(char **info);
void	env_add(char *info, char **env);
int		ft_export(char **info, char **envp, int fd);
void	read_cmd(char **info, int fd);
int		ft_quote_cnt(char *line, int flag);
char	*ft_quote(char *line);
int		ft_quote_cmd(char *line);
int		ft_cmd(char **infos);
void	fork_process(int *pipefd, char **cmd, char **path, int i);
void	ft_pipe(char *cm);
void	read_env(char **info, int fd);

#endif
