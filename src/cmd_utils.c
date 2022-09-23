/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 00:57:23 by dmillan           #+#    #+#             */
/*   Updated: 2022/09/23 22:37:15 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_add_cmd(t_cmd_list *cmd_list,
			char **pipe_part, int fd_in, int fd_out)
{
	t_cmd	*cmd_new;
	t_cmd	*cmd_temp;

	cmd_new = (t_cmd *)malloc(sizeof(t_cmd));
	cmd_new->cmd = pipe_part;
	cmd_new->fd_in = fd_in;
	cmd_new->fd_out = fd_out;
	cmd_new->pid = 0;
	cmd_new->exitcode = 0;
	if (!cmd_list->cmds)
		cmd_list->cmds = NULL;
	cmd_temp = cmd_list->cmds;
	cmd_new->next = cmd_temp;
	cmd_list->cmds = cmd_new;
}

void	ft_cmd_free(t_cmd_list *cmd_list)
{
	int		i;
	t_cmd	*tmp;
	t_cmd	*tmp_prev;

	tmp = cmd_list->cmds;
	while (tmp != NULL)
	{
		i = 0;
		while (tmp->cmd[i] != NULL)
			free(tmp->cmd[i++]);
		free (tmp->cmd);
		tmp_prev = tmp;
		tmp = tmp->next;
		free (tmp_prev);
	}
	cmd_list->cmds = 0;
}
