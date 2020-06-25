#ifndef MINISHELL_H
# define MINISHELL_H

#include "ft_util.h"
#include "get_next_line.h"
#include <sys/wait.h>
#include <dirent.h>

extern int g_ret;
extern char **g_env;

int		redirection(char **redir, int r_flag);
int	ft_echo(char **info, char **redir, int r_flag);
int		ft_pwd(char **info, char **redir, int r_flag);
int		ft_cd(char **info);
int ft_quote_cnt(char *line, int flag);
char	*ft_quote(char *line);
int	ft_unset(char **info, char **envp);
void env_add(char *info, char **env);
int	ft_export(char **info, char **envp, char **redir, int r_flag);
int newline_valid(char **info);
void	read_cmd(char **info, char **redir, int r_flag, char **envp);
int ft_quote_cnt(char *line, int flag);
char	*ft_quote(char *line);
int	ft_quote_cmd(char *line);
int		ft_env_valid(char **info);
int	ft_print_env(char **envp, char **redir, int r_flag);
int	ft_print_env_1(char **info);
int	ft_env(char **info, char **envp, char **redir, int r_flag);
char **ft_cpenv(char **envp);
int	ft_cmd(char *cmd);
char **ft_find_path();
char *ft_pathjoin(char **path, char **cmd);
void child_process(char **info, int *pipefd, char *path_cmd);
void parent_process(int *pipefd, char **path, char **cmd, int i);
void ft_pipe(char *cm);
void		read_env(char **info, char **redir, int r_flag);

#endif