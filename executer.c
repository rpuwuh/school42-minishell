/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 01:23:32 by bpoetess          #+#    #+#             */
/*   Updated: 2022/08/02 06:41:43 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	executecmd(t_cmd *cmd, t_cmd_list *cmd_list)
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
		return (choosefunc(cmd, cmd_list));
	if (!ft_strchr(*cmd->cmd, '/'))
		path = searchbinarypath(*cmd->cmd, cmd_list->env);
	else
		path = ft_strdup(*cmd->cmd);
	if (path && access(path, X_OK) != -1)
		execve(path, cmd->cmd, cmd_list->env);
	return (0);
}

static void	clearlistcmds(t_cmd_list *cmdlist)
{
	t_cmd	*cmd;
	// t_cmd	*cmdtemp;
	// int		i;

	cmd = cmdlist->cmds;
	while (cmd)
	{
		// i = 0;
		// while (cmd->cmd && cmd->cmd[i])
			// free (cmd->cmd[i++]);
		if (cmd->cmd)
			free (cmd->cmd);
		// cmdtemp = cmd;
		cmd = cmd->next;
		// free(cmdtemp);
	}
	// free(cmdlist);
}

static int	clearexecuter(t_cmd_list *cmd_list, int lastcode)
{
	t_cmd	*cmd;
	int		res;

	cmd = cmd_list->cmds;
	while (cmd->next)
		cmd = cmd->next;
	printf ("waited cmd is %s, pid is %d\n", *cmd->cmd, cmd->pid);
	if (cmd->pid)
		waitpid(cmd->pid, &res, WUNTRACED | WEXITED);
	else
		res = lastcode;
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
	clearlistcmds(cmd_list);
	return (res);
}

int	executecmds(t_cmd_list *cmd_list)
{
	t_cmd	*cmd;
	int		i;

	i = 0;
	if (checkexecutabless(cmd_list))
		return (1);
	cmd = cmd_list->cmds;
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

void	executer(t_cmd_list *cmd_list, t_env_v *env)
{
	int	i;

	i = executecmds(cmd_list);
	while (ft_strncmp(env->name, "?", ft_strlen("?")))
		env = env->next;
	if (env->name && env->value)
		free (env->value);
	env->value = ft_itoa(i);
}
