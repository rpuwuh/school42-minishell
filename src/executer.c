/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 01:23:32 by bpoetess          #+#    #+#             */
/*   Updated: 2022/09/27 03:05:52 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	close_extrafds(t_cmd *cmd, t_cmd_list *cmd_list)
{
	t_cmd	*cmd_tmp;

	if (!cmd_list || !cmd_list->cmds || !cmd)
		return ;
	cmd_tmp = cmd_list->cmds;
	while (cmd_tmp)
	{
		if (cmd_tmp != cmd && cmd_tmp->fd_in != 0)
		{
			close (cmd_tmp->fd_in);
			cmd_tmp->fd_in = 0;
		}
		if (cmd_tmp != cmd && cmd_tmp->fd_out != 1)
		{
			close (cmd_tmp->fd_out);
			cmd_tmp->fd_out = 1;
		}
		cmd_tmp = cmd_tmp->next;
	}
}

static void	executecmd(t_cmd *cmd, t_cmd_list *cmd_list)
{
	char	*path;

	close_extrafds(cmd, cmd_list);
	if (cmd->fd_in > 0)
	{
		dup2(cmd->fd_in, 0);
		close (cmd->fd_in);
	}
	if (cmd->fd_out != 1 && cmd->fd_out)
	{
		dup2(cmd->fd_out, 1);
		close (cmd->fd_out);
	}
	if (builtin_check(*cmd->cmd) == 2)
		exit (choosefunc(cmd, cmd_list));
	if (!ft_strchr(*cmd->cmd, '/'))
		path = searchbinarypath(*cmd->cmd, cmd_list->env_list);
	else
		path = ft_strdup(*cmd->cmd);
	ft_signals_run(4);
	if (path && access(path, X_OK) != -1)
		execve(path, cmd->cmd, reassemble_env(cmd_list));
	exit (255);
}

int	executecmds(t_cmd_list *cmd_list)
{
	t_cmd	*cmd;

	if (checkexecutabless(cmd_list))
		return (127);
	cmd = cmd_list->cmds;
	ft_signals_run(3);
	while (cmd)
	{
		if (builtin_check(*cmd->cmd) == 1)
			cmd->exitcode = choosefunc(cmd, cmd_list);
		else
		{
			cmd->pid = fork();
			if (cmd->pid < 0)
				exit (10);
			if (!cmd->pid)
				executecmd(cmd, cmd_list);
		}
		cmd = cmd->next;
	}
	return (clearexecuter(cmd_list));
}

void	ft_executer(t_cmd_list *cmd_list, t_env_v *env)
{
	t_cmd	*cmds;

	create_pipes(cmd_list);
	cmd_list->env_list = env;
	cmds = cmd_list->cmds;
	if (!cmd_list || !cmds)
	{
		ft_env_replace(&env, "?", ft_strdup("1"), 0);
		return ;
	}
	while (cmds)
	{
		if (cmds->fd_in == -1 || cmds->fd_out == -1)
		{
			ft_env_replace(&env, "?", ft_strdup("1"), 0);
			return ;
		}
		cmds = cmds->next;
	}
	cmds = cmd_list->cmds;
	ft_env_replace(&env, "?", ft_itoa(executecmds(cmd_list)), 0);
}
