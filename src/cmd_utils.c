/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 00:57:23 by dmillan           #+#    #+#             */
/*   Updated: 2022/08/10 00:57:53 by dmillan          ###   ########.fr       */
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
	if (!cmd_list->cmds)
		cmd_list->cmds = NULL;
	cmd_temp = cmd_list->cmds;
	cmd_new->next = cmd_temp;
	cmd_list->cmds = cmd_new;
}

void	ft_cmdlist_free(t_cmd_list *cmd_list)
{
	int		i;
	t_cmd	*tmp;

	tmp = cmd_list->cmds;
	while (tmp != NULL)
	{
		tmp = cmd_list->cmds->next;
		i = 0;
		while (cmd_list->cmds->cmd[i] != NULL)
			free(cmd_list->cmds->cmd[i++]);
		cmd_list->cmds = tmp;
	}
	//free(cmd_list);
}
