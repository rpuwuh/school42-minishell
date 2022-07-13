/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 01:23:32 by bpoetess          #+#    #+#             */
/*   Updated: 2022/07/13 21:13:44 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	choosefunc(t_cmd *cmd, char **env)
{
	if (!ft_strncmp(*cmd->cmd, "builtin", ft_strlen("builtin")))
	{
		if (!ft_strncmp(cmd->cmd[1], "pwd", ft_strlen("pwd")))
			builtin_pwd();
		if (!ft_strncmp(cmd->cmd[1], "echo", ft_strlen("echo")))
			builtin_echo(&(cmd->cmd)[2]);
		if (!ft_strncmp(cmd->cmd[1], "env", ft_strlen("env")))
			builtin_echo(env);
	}
	else
		execve(*(cmd->cmd), &(cmd->cmd)[1], env);
}

static void	executecmd(t_cmd *cmd, char **env, int *fds)
{
	dup2(fds[1], 1);
	close(fds[0]);
	close(fds[1]);
	choosefunc(cmd, env);
}

static void	executelastcmd(t_cmd_list *cmd_list, t_cmd *cmd)
{
	cmd->pid = fork();
	if (cmd->pid < 0)
		exit (10);
	if (!cmd->pid)
	{
		dup2(cmd->fd_out, 1);
		choosefunc(cmd, cmd_list->env);
	}
	waitpid(cmd->pid, 0, 0);
	cmd = cmd_list->cmds;
	while (cmd)
	{
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
	int		fds[2];

	cmd = cmd_list->cmds;
	dup2(cmd_list->cmds->fd_in, 0);
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
		close(fds[0]);
		cmd = cmd->next;
	}
	executelastcmd(cmd_list, cmd);
}
