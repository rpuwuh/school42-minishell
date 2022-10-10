/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 00:57:23 by dmillan           #+#    #+#             */
/*   Updated: 2022/10/10 00:38:51 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_add_cmd(t_cmd_list *cmd_list,
			char **pipe_part, int fd_in, int fd_out)
{
	t_cmd	*cmd_new;
	t_cmd	*cmd_temp;
	int		i;

	cmd_new = (t_cmd *)malloc(sizeof(t_cmd));
	i = 0;
	while (pipe_part[i] != NULL)
		i++;
	cmd_new->cmd = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (pipe_part[i] != NULL)
	{
		cmd_new->cmd[i] = ft_strdup(pipe_part[i]);
		i++;
	}
	cmd_new->cmd[i] = NULL;
	cmd_new->fd_in = fd_in;
	cmd_new->fd_out = fd_out;
	cmd_new->pid = 0;
	cmd_new->exitcode = 0;
	if (!cmd_list->cmds)
		cmd_list->cmds = NULL;
	cmd_temp = cmd_list->cmds;
	cmd_new->next = cmd_temp;
	cmd_list->cmds = cmd_new;

	i = 0;
	int j = 0;
	cmd_temp = cmd_list->cmds;
	while (cmd_temp != NULL)
	{
		i = 0;
		while (cmd_temp->cmd[i] != NULL)
		{
			printf("cmd_%d = %s\n", i, cmd_temp->cmd[i]);
			i++;
		}
		printf("count = %d\n", j);
		j++;
		cmd_temp = cmd_temp->next;
	}
}

void	ft_cmd_free(t_cmd_list *cmd_list)
{
	int		i;
	t_cmd	*tmp;
	t_cmd	*tmp_next;

	tmp = cmd_list->cmds;
	printf("check cmd\n");
	tmp_next = NULL;
	while (tmp != NULL)
	{
		i = 0;
		while (tmp && tmp->cmd && tmp->cmd[i])
		{
			printf("cmd = %s\n", tmp->cmd[i]);
			free(tmp->cmd[i++]);
		}
		printf("check cmd-2\n");
		if (tmp && tmp->cmd)
			free (tmp->cmd);
		if (cmd_list->cmds->next)
			tmp_next = cmd_list->cmds->next;
		if (tmp)
		{
			free (tmp);
			printf("check cmd-2-1\n");
		}
		cmd_list->cmds = tmp_next;
		tmp = cmd_list->cmds;
		printf("check cmd-3\n");
	}
}
