/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 12:11:23 by sfournio          #+#    #+#             */
/*   Updated: 2022/07/08 17:56:12 by dmillan          ###   ########.fr       */
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
# include "libft.h"
# include <termios.h>
# include <signal.h>
# include <curses.h>
# include <term.h>

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

# define DEFAULT "\001\033[0;39m\002"
# define GRAY "\001\033[1;90m\002"
# define RED "\001\033[1;91m\002"
# define GREEN "\001\033[1;92m\002"
# define YELLOW "\001\033[1;93m\002"
# define BLUE "\001\033[1;94m\002"
# define MAGENTA "\001\033[1;95m\002"
# define CYAN "\001\033[1;96m\002"
# define WHITE "\001\033[0;97m\002"

# define UNKNOWN -1
# define CMD 0
# define PIPE 1
# define DELIMITER 2
# define APPEND 3
# define INPUT 4
# define TRUNC 5
# define SEP 6

# define CTRL_D 1
# define UNKNOWN_COMMAND 0
# define TRUE 1
# define FALSE 0

typedef struct s_cmd
{
	char				*cmd;
	char				*arguments;
	bool				redirection;
	pid_t				fd;
	struct s_cmd	*next;
}						t_cmd;

typedef struct s_cmd_list
{
	int				count;
	struct s_cmd	*cmd_list;
	int 			fd_out;
}					t_cmd_list;

typedef struct s_env_v
{
	char			*name;
	char			*value;
	int				export;
	struct s_env_v	*next;
}					t_env_v;

typedef struct s_token
{
	int				idx;
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}				t_token;

typedef enum e_token_type{
	NONE,
	ARG,
	TRUNC,
	INPUT,
	APPEND,
	PIPE,
	HEREDOC
}			t_token_type;


#endif