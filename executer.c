/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 01:23:32 by bpoetess          #+#    #+#             */
/*   Updated: 2022/07/16 04:29:57 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	executecmd(t_cmd *cmd, char **env)
{
	char	*path;

	if (cmd->fd_in)
	{
		dup2(cmd->fd_in, 0);
		close (cmd->fd_in);
	}
	if (cmd->fd_out != 1)
	{
		dup2(cmd->fd_out, 1);
		close (cmd->fd_out);
	}
	printf("cmd = %s\n", *cmd->cmd);
	if (builtin_check(*cmd->cmd) == 2)
		choosefunc(cmd, env);
	if (!ft_strchr(*cmd->cmd, '/'))
		path = searchbinarypath(*cmd->cmd, env);
	else
		path = ft_strdup(*cmd->cmd);
	if (path && access(path, X_OK) != -1)
		execve(path, cmd->cmd, env);
}

static void	clearexecuter(t_cmd_list *cmd_list)
{
	t_cmd	*cmd;

	cmd = cmd_list->cmds;
	while (cmd->next)
		cmd = cmd->next;
	printf ("waited cmd is %s, pid is %d\n", *cmd->cmd, cmd->pid);
	if (cmd->pid)
		waitpid(cmd->pid, 0, WUNTRACED | WEXITED);
	cmd = cmd_list->cmds;
	while (cmd)
	{
		if (cmd->pid)
			kill(cmd->pid, SIGTERM);
		if (cmd->fd_in)
			close(cmd->fd_in);
		if (cmd->fd_out != 1)
			close(cmd->fd_out);
		cmd = cmd->next;
	}
}

void	executecmds(t_cmd_list *cmd_list)
{
	t_cmd	*cmd;

	cmd = cmd_list->cmds;
	if (checkexecutabless(cmd_list))
		return ;
	while (cmd)
	{
		if (builtin_check(*cmd->cmd) == 1)
			choosefunc(cmd, cmd_list->env);
		else
		{
			cmd->pid = fork();
			if (cmd->pid < 0)
				exit (10);
			if (!cmd->pid)
				executecmd(cmd, cmd_list->env);
		}
		cmd = cmd->next;
	}
	clearexecuter(cmd_list);
}
