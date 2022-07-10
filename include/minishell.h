/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 12:11:23 by sfournio          #+#    #+#             */
/*   Updated: 2022/07/11 00:17:52 by dmillan          ###   ########.fr       */
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

# define BLUE "\033[38;5;36m"
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
	char				*cmd;
	char				*arguments;
	bool				redirection;
	pid_t				fd;
	struct s_cmd		*next;
}						t_cmd;

typedef struct s_cmd_list
{
	int				count;
	struct s_cmd	*cmd_list;
	int				fd_out;
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

typedef enum e_quote_type{
	NONE,
	SINGLE,
	DOUBLE
}			t_quote_type;

typedef struct s_token
{
	int				idx;
	t_token_type	type;
	char			*value;
	t_quote_type	quote;
	struct s_token	*next;
}				t_token;

int				ft_shell_init(t_env_v	**env, char **envp, char *prompt);
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
void			ft_parser(char *line, t_env_v **env, char	**envp);
char			*ft_remove_extra_spaces(char *s);
int				ft_quotes_open(char *s, int pos, char symb1, char symb2);
static int		ft_get_fd(int	*fd_list);
static int		ft_redirect_check(char *s);
static int		ft_quotes_check(char *s);
t_token			*ft_tokens_init(void);
static void		ft_tokens_get(t_token *tokens, char **line);

#endif