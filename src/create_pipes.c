/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 20:00:43 by bpoetess          #+#    #+#             */
/*   Updated: 2022/09/19 20:01:23 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	create_pipes(t_cmd_list *cmd_list)
{
	t_cmd	*cmd;
	int		fds[2];

	if (!cmd_list || !cmd_list->cmds)
		return ;
	cmd = cmd_list->cmds;
	while (cmd && cmd->next)
	{
		if (pipe(fds) < 0)
			exit(EPIPE);
		if (cmd->fd_out == 1)
			cmd->fd_out = fds[1];
		else
			close(fds[1]);
		if (cmd->next->fd_in == 0)
			cmd->next->fd_in = fds[0];
		else
			close(fds[0]);
		cmd = cmd->next;
	}
}
