/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 01:23:32 by bpoetess          #+#    #+#             */
/*   Updated: 2022/07/08 05:47:00 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	executecmd(t_cmd *cmd, char **env, int *fds)
{
	dup2(fds[1], 1);
	close(fds[0]);
	execve(*(cmd->cmd), &(cmd->cmd)[1], env);
}

static void	executelastcmd(t_cmd_list *cmd_list, t_cmd *cmd)
{
	cmd->pid = fork();
	if (cmd->pid < 0)
		exit (10);
	if (!cmd->pid)
	{
		dup2(cmd_list->fd_out, 1);
		execve(*(cmd->cmd), (cmd->cmd + 1), (cmd_list->env));
	}
	waitpid(cmd->pid, 0, 0);
	cmd = cmd_list->cmds;
	while (cmd)
	{
		kill(cmd->pid, SIGTERM);
		cmd = cmd->next;
	}
}

void	executecmds(t_cmd_list *cmd_list)
{
	t_cmd	*cmd;
	int		fds[2];

	cmd = cmd_list->cmds;
	while (cmd->next)
	{
		if (pipe(fds) < 0)
			exit (32);
		cmd->pid = fork();
		if (cmd->pid < 0)
			exit (10);
		if (!cmd->pid)
			executecmd(cmd, cmd_list->env, fds);
		dup2(fds[0], 0);
		close(fds[1]);
		cmd = cmd->next;
	}
	executelastcmd(cmd_list, cmd);
}
