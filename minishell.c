/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 22:45:04 by bpoetess          #+#    #+#             */
/*   Updated: 2022/07/08 05:47:19 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_cmd_list	list;
	t_cmd		cmd1;
	t_cmd		cmd2;

	(void) argc;
	(void) env;
	(void) argv;
	list.cmds = &cmd1;
	list.fd_out = 1;
	// list.fd_out = open ("123", 0x209, 0644);
	cmd1.next = &cmd2;
	cmd2.next = 0;
	cmd1.cmd = malloc (sizeof(char *) * 4);
	cmd2.cmd = malloc (sizeof(char *) * 4);
	// *cmd1.cmd = "/usr/bin/yes";
	// *(cmd1.cmd + 1) = "yes";
	// *cmd2.cmd = "/usr/bin/head";
	// *(cmd2.cmd + 1) = "head";
	*cmd1.cmd = "/bin/ls";
	*(cmd1.cmd + 1) = "/bin/ls";
	*(cmd1.cmd + 2) = "-la";
	*(cmd1.cmd + 3) = 0;
	*cmd2.cmd = "/usr/bin/grep";
	*(cmd2.cmd + 1) = "/usr/bin/grep";
	*(cmd2.cmd + 2) = "total";
	*(cmd2.cmd + 3) = 0;
	executecmds(&list);
	exit (0);
}
