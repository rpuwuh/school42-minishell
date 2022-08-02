/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 22:44:27 by bpoetess          #+#    #+#             */
/*   Updated: 2022/08/02 08:25:45 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <signal.h>
# include <fcntl.h>

# include <readline/readline.h>
# include <readline/history.h>

# include "libft/libft.h"

/*# include </goinfre/bpoetess/.brew/Cellar/readline/8.1.2/include/
	readline/readline.h>
# include </goinfre/bpoetess/.brew/Cellar/readline/8.1.2/include/readline/
history.h>*/

/*

** cmd is for execve, cmd[0] is a path to a binary file,
** cmd [1] and so on are for argv to turn on the binary file
** env is for environment to turn on the binary file
** pid is for process id of a running binary file process
** next is for next command
 
*/

typedef struct s_env_v
{
	char			*name;
	char			*value;
	int				export;
	struct s_env_v	*next;
}					t_env_v;

typedef struct s_cmd	t_cmd;

struct	s_cmd
{
	char		**cmd;
	pid_t		pid;
	int			fd_in;
	int			fd_out;
	t_cmd		*next;
};

typedef struct s_cmd_list
{
	t_cmd	*cmds;
	t_env_v	*env_list;
	char	**env;
}	t_cmd_list;

int		executecmds(t_cmd_list *cmd_list);

int		builtin_check(char *cmd);
int		choosefunc(t_cmd *cmd, t_cmd_list *cmd_list);

int		builtin_echo(char **args);
int		builtin_pwd(void);
int		builtin_cd(char *path, char **env);
int		builtin_exit(char **s);

char	*searchbinarypath(char *cmd, char **env);
int		checkexecutabless(t_cmd_list *cmd_list);

int		checkexecutabless(t_cmd_list *cmd_list);

#endif
