#ifndef MINISHELL_H
# define MINISHELL_H

#include "ft_util.h"
#include <sys/wait.h>
#include <dirent.h>
#include <fcntl.h>

extern int	g_ret;
extern char **g_env;

void	ft_pipe(char *cm);
int		ft_env_valid(char **info);
int	ft_print_env(char **envp, char **redir, int r_flag);
void	ft_print_env_1(char **info);
void	env_add(char *info, char **env);
void	ft_env(char **info, char **envp, char **redir, int r_flag);
int		ft_quote_cnt(char *line, int flag);
char	*ft_quote(char *line);
int		ft_quote_cmd(char *line);
int		redirection(char **redir, int r_flag);
void	ft_unset(char **info, char **envp);
void	ft_export(char **info, char **envp, char **redir, int r_flag);
void	ft_echo(char **info, char **redir, int r_flag, int new_flag);
int		ft_pwd(char **info, char **redir, int r_flag);
int		ft_cd(char **info);
int		read_cmd(char **info, char **redir, int r_flag, char **envp);
int		ft_cmd(char *cmd);
void	fork_process(int *pipefd, char **cmd, char **path, int i);


#endif