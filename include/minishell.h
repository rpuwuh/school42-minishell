/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 12:11:23 by sfournio          #+#    #+#             */
/*   Updated: 2022/07/18 00:04:16 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <termios.h>
# include <string.h>
# include <signal.h>
# include <curses.h>
# include <term.h>
# include "libft.h"
# include <sys/ioctl.h>

# define INCORRECT_INPUT "no arguments required for ./minishell"
# define CMD_NOTFOUND "command not found"
# define OLDPWD_CODE 667
# define OLDPWD_ERR "OLDPWD not set"
# define ENOENT_ERR "No such file or directory"
# define ENOTDIR_ERR "Not a directory"
# define EACCES_ERR "Permission denied"
# define KERNEL_REG "Failed to catch interruptions with kernel"
# define INV_ID "not a valid identifier"
# define UNEX_TOKEN "syntax error near unexpected token"
# define IS_DIR "is a directory"

//# define BLUE "\033[38;5;36m"
# define BLUE "\001\033[1;94m\002"
# define RED "\033[0;31m"
# define YELLOW "\033[0;33m"
# define RESETCOLOR "\033[0m"

# define CTRL_D 1
# define UNKNOWN_COMMAND 0
# define TRUE 1
# define FALSE 0

int	g_status;

typedef struct s_cmd
{
	char				**cmd;
	int					fd_in;
	int					fd_out;
	pid_t				pid;
	struct s_cmd		*next;
}						t_cmd;

typedef struct s_cmd_list
{
	struct s_cmd	*cmds;
	char			**envp;
}					t_cmd_list;

typedef struct s_env_v
{
	char			*name;
	char			*value;
	int				export;
	struct s_env_v	*next;
}					t_env_v;

typedef enum e_token_type{
	NONE,
	ARG,
	TRUNC,
	INPUT,
	APPEND,
	PIPE,
	HEREDOC
}			t_token_type;

typedef struct s_token
{
	int				idx;
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}				t_token;

int				ft_shell_init(t_env_v	**env, char **envp);
void			ft_exit_with_error(char *func, char *msg);
void			ft_exit(char **args, int ctrl_d, t_env_v *env_v);
char			*ft_env_get_value(t_env_v *env_v, char *name);
char			*ft_get_prompt(t_env_v	**env);
t_env_v			*ft_env_create(void);
void			ft_env_add(t_env_v **env_v, char *name,
					char *value, int export);
void			ft_env_free(t_env_v **env_v);
void			ft_env_init(t_env_v **env, char **envp);
void			ft_env_replace(t_env_v **env_v, char *name,
					char *value, int export);
void			ft_parser(char *line, t_env_v **env, t_cmd_list *cmd_list);
char			*ft_remove_extra_spaces(char *s);
void			ft_quotes_remove(t_token **tokens, t_env_v **env);
int				ft_quotes_open(char *s, int pos, char symb1, char symb2);
int				ft_redirect_check(char *s);
int				ft_quotes_check(char *s);
t_token			*ft_tokens_init(void);
void			ft_tokens_get(t_token *tokens, char **line);
void			ft_pipe_parse(t_token **tokens, t_cmd_list *cmd_list);
void			ft_pipe_process(t_token **tokens_part, t_cmd_list *cmd_list);
char			**ft_tokens_convert(t_token **tokens);
int				ft_get_fd(int *fd_list);
int				ft_redirect(char *filename, int type);
int				**ft_redirect_init(t_token **tokens);
int				ft_fd_list_check(t_token *tokens,
					int type_a, int type_b, int *fd_list);
void			ft_add_cmd(t_cmd_list *cmd_list,
					char **pipe_part, int fd_in, int fd_out);
void			ft_heredoc_remove(t_cmd_list *cmd_list);
void 			ft_executer(t_cmd_list *cmd_list);
void			ft_tokens_free(t_token *tokens);
int				ft_redirections_exist(t_token **tokens);
void			ft_redirections_parse(t_token **tokens, t_cmd_list *cmd_list);
void			ft_token_add(t_token **tokens, t_token *token_to_add);
void			ft_cmdlist_free(t_cmd_list *cmd_list);

#endif