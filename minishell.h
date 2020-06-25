#ifndef MINISHELL_H
# define MINISHELL_H

#include "ft_util.h"
#include "get_next_line.h"
#include <sys/wait.h>
#include <dirent.h>

extern int g_ret;
extern char **g_env;

int		redirection(char **redir, int r_flag);
int		ft_echo(char **info, char **redir, int r_flag);
int		ft_pwd(char **info, char **redir, int r_flag);
int		ft_cd(char **info);
int		ft_unset(char **info, char **envp);
int		ft_env(char **info, char **envp, char **redir, int r_flag);
int		ft_env_valid(char **info);
int		ft_print_env(char **envp, char **redir, int r_flag);
int		ft_print_env_1(char **info);
void	env_add(char *info, char **env);
int		ft_export(char **info, char **envp, char **redir, int r_flag);
void	read_cmd(char **info, char **redir, int r_flag, char **envp);
int		ft_quote_cnt(char *line, int flag);
char	*ft_quote(char *line);
int		ft_quote_cmd(char *line);
int		ft_cmd(char *cmd);
void	fork_process(int *pipefd, char **cmd, char **path, int i);
void	ft_pipe(char *cm);
void	read_env(char **info, char **redir, int r_flag);

#endif