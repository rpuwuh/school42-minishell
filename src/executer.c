/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 01:23:32 by bpoetess          #+#    #+#             */
/*   Updated: 2022/09/16 20:07:22 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	executecmd(t_cmd *cmd, t_cmd_list *cmd_list)
{
	char	*path;

	printf("cmd = %s\n", *cmd->cmd); // delete this line before release
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

static int	show_stoping_message(int exitcode)
{
	if (WIFSIGNALED(exitcode))
	{
		if (WTERMSIG(exitcode) == SIGQUIT)
		{
			ft_putstr_fd("Quit: 3\n", 1);
			return (131);
		}
		else if (WTERMSIG(exitcode) == SIGINT)
		{
			ft_putstr_fd("\n", 1);
			return (132);
		}
	}
	return (exitcode);
}

static int	clearexecuter(t_cmd_list *cmd_list, int lastcode)
{
	t_cmd	*cmd;
	int		res;

	cmd = cmd_list->cmds;
	while (cmd && cmd->next)
		cmd = cmd->next;
	printf ("waited cmd is %s, pid is %d\n", *cmd->cmd, cmd->pid); // delete this line before release
	if (cmd->pid)
		waitpid(cmd->pid, &res, WUNTRACED);
	else
		res = lastcode;
	ft_signals_run(1);
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
	res = show_stoping_message(res);
	return (res);
}

int	executecmds(t_cmd_list *cmd_list)
{
	t_cmd	*cmd;
	int		i;

	i = 0;
	if (checkexecutabless(cmd_list))
		return (127);
	cmd = cmd_list->cmds;
	ft_signals_run(3);
	while (cmd)
	{
		if (builtin_check(*cmd->cmd) == 1)
			i = choosefunc(cmd, cmd_list);
		else
		{
			cmd->pid = fork();
			if (cmd->pid < 0)
				exit (10);
			if (!cmd->pid)
				i = executecmd(cmd, cmd_list);
		}
		cmd = cmd->next;
	}
	return (clearexecuter(cmd_list, i));
}

void	ft_executer(t_cmd_list *cmd_list, t_env_v *env)
{
	int		i;
	t_cmd	*cmds;

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
	while (cmds) // delete this line before release
	{ // delete this line before release
		i = 0; // delete this line before release
		while (cmds->cmd[i]) // delete this line before release
		{ // delete this line before release
			printf("command_%d = %s\n", i, cmds->cmd[i]); // delete this line before release
			i++; // delete this line before release
		} // delete this line before release
		printf("fd_in = %d\n", cmds->fd_in); // delete this line before release
		printf("fd_out = %d\n", cmds->fd_out); // delete this line before release
		cmds = cmds->next;  // delete this line before release
	} // delete this line before release
	ft_env_replace(&env, "?", ft_itoa(executecmds(cmd_list)), 0);
}
