/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkexecutables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 01:30:38 by bpoetess          #+#    #+#             */
/*   Updated: 2022/08/10 00:31:59 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	checkcmdshowmessage(char *path, char *cmd)
{
	if (!(path || access(path, 0) != -1))
	{
		printf("minishell: no such file or directory: %s\n", cmd);
		if (path)
			free(path);
		return (1);
	}
	if (access(path, X_OK) == -1)
	{
		printf("minishell: %s: Permission denied\n", cmd);
		free(path);
		return (1);
	}
	free(path);
	return (0);
}

int	checkexecutabless(t_cmd_list *cmd_list)
{
	t_cmd	*cmd;
	int		result;
	char	*path;

	cmd = cmd_list->cmds;
	result = 0;
	while (cmd)
	{
		if (!builtin_check(*cmd->cmd))
		{
			if (!ft_strchr(*cmd->cmd, '/'))
				path = searchbinarypath(*cmd->cmd, cmd_list->env);
			else
				path = ft_strdup(*cmd->cmd);
			if (checkcmdshowmessage(path, *cmd->cmd))
				result = 1;
		}
		cmd = cmd->next;
	}
	return (result);
}
