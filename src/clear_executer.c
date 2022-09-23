/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_executer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:02:09 by bpoetess          #+#    #+#             */
/*   Updated: 2022/09/23 21:00:17 by bpoetess         ###   ########.fr       */
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

int	clearexecuter(t_cmd_list *cmd_list, int lastcode)
{
	t_cmd	*cmd;
	int		res;

	cmd = cmd_list->cmds;
	while (cmd && cmd->next)
		cmd = cmd->next;
	close_fds(cmd_list);
	if (cmd->pid)
		waitpid(cmd->pid, &res, WUNTRACED);
	else if (!cmd->pid)
		res = lastcode;
	cmd = cmd_list->cmds;
	while (cmd)
	{
		if (cmd->next && cmd->pid)
			kill(cmd->pid, SIGTERM);
		cmd = cmd->next;
	}
	ft_signals_run(1);
	res = show_stoping_message(res);
	return (res % 255);
}
