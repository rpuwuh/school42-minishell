/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_executer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:02:09 by bpoetess          #+#    #+#             */
/*   Updated: 2022/09/23 21:46:47 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**	checks is the process stopped by signal
 *	and if it was then checks was it SIGQUIT or SIGINT
 *	and if it was then changes exit code */

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

static void	addexitcode(t_cmd_list *cmd_list, pid_t pid, int exitcode)
{	
	t_cmd	*cmd;

	cmd = cmd_list->cmds;
	while (cmd && cmd->pid != pid)
		cmd = cmd->next;
	if (cmd && cmd->pid == pid)
		cmd->exitcode = exitcode;
}

static int	waitlistofcmds(t_cmd_list *cmd_list)
{
	t_cmd	*cmd;
	int		exitcode;
	pid_t	pid;

	if (!cmd_list || !cmd_list->cmds)
		return (ENOMEM);
	cmd = cmd_list->cmds;
	while (cmd)
	{
		if (cmd && cmd->pid)
		{
			pid = waitpid(-1, &exitcode, WUNTRACED);
			addexitcode(cmd_list, pid, exitcode);
		}
		cmd = cmd->next;
	}
	cmd = cmd_list->cmds;
	while (cmd && cmd->next)
		cmd = cmd->next;
	return (cmd->exitcode);
}

int	clearexecuter(t_cmd_list *cmd_list)
{
	int		res;

	close_fds(cmd_list);
	res = waitlistofcmds(cmd_list);
	ft_signals_run(1);
	res = show_stoping_message(res);
	return (res % 255);
}
