/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 22:45:04 by bpoetess          #+#    #+#             */
/*   Updated: 2022/08/02 08:13:55 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_cmd_list	list;
	t_cmd		cmd1;
	t_cmd		cmd2;
	int			fds[2];

	(void) argc;
	(void) env;
	(void) argv;
	list.cmds = &cmd1;
	list.env = env;
	// list.fd_out = 1;
	pipe(fds);
	cmd1.fd_in = open ("123", O_RDONLY);
	cmd1.fd_out = fds[1];
	cmd2.fd_in = fds[0];
	printf("%d\n", list.cmds->fd_in);
	cmd2.fd_out = 1;
	// cmd2.fd_out = open ("123", 0x601, 0644);
	printf("%d\n", cmd2.fd_out);
	// list.fd_in = open("./Makefile", O_RDONLY);
	// dup2(list.fd_in, 0);
	// list.fd_in = open("./minishell.c", O_RDONLY);
	// dup2(list.fd_in, 0);
	// list.fd_out = open ("123", 0x209, 0644);
	cmd1.next = &cmd2;
	cmd2.next = 0;
	cmd1.cmd = malloc (sizeof(char *) * 4);
	cmd2.cmd = malloc (sizeof(char *) * 4);
	// *cmd1.cmd = "/usr/bin/yes";
	// *(cmd1.cmd + 1) = "yes";
	// *(cmd1.cmd + 2) = 0;
	*cmd2.cmd = "head";
	*(cmd2.cmd + 1) = 0;
	// *cmd1.cmd = "/bin/ls";
	// *(cmd1.cmd + 1) = "/bin/ls";
	// *(cmd1.cmd + 2) = "-la";
	// *(cmd1.cmd + 3) = 0;
	*cmd1.cmd = "cat";
	*(cmd1.cmd + 1) = 0;
	// *cmd2.cmd = "/usr/bin/grep";
	// *(cmd2.cmd + 1) = "/usr/bin/grep";
	// *(cmd2.cmd + 2) = "minishell.c";
	*(cmd2.cmd + 3) = 0;
	executecmds(&list);
	exit (0);
}
