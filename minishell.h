/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 12:11:23 by sfournio          #+#    #+#             */
/*   Updated: 2022/07/06 00:09:38 by dmillan          ###   ########.fr       */
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

# define INCORRECT_INPUT "Incorrect input: no arguments required"
# define CMD_NOTFOUND "command not found"
# define OLDPWD_CODE 667
# define OLDPWD_ERR "OLDPWD not set"
# define ENOENT_ERR "No such file or directory"
# define ENOTDIR_ERR "Not a directory"
# define EACCES_ERR "Permission denied"
# define KERNEL_REGISTER "failed to register interrupts with kernel"
# define INV_ID "not a valid identifier"
# define UNEX_TOKEN "syntax error near unexpected token"
# define IS_DIR "is a directory"

# define UNKNOWN -1
# define CMD 0
# define PIPE 1
# define DELIMITER 2
# define APPEND 3
# define INPUT 4
# define TRUNC 5
# define SEP 6

typedef struct s_command
{
	char		**args;
	int			nb_args;
}				t_command;

typedef struct s_token	t_token;

// Struct for tokens we get after we parse

typedef struct s_token
{
	char			*value;
	int				type;
	t_token			*nxt;
	t_token			*prv;
}					t_token;

// Global variable -- all data for our shell

typedef struct s_shell
{
	int				value;
	char			**envp;
	char			**path_list;
	char			*on_start;
	t_token			*tokens;
	char			*prompt;
	int				fd_input;
	int				fd_output;
	int				double_slash;
	t_token			*cmd_token;
	int				in_pipe;
	int				out_pipe;
	int				l_pipe[2];
	int				r_pipe[2];
	t_cmd			*cmd;
	int				input_type;
	char			*delim;
	char			*delim_str;
	int				delim_pipes[2];
}					t_shell;

t_shell					g_shell;

#endif