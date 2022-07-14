/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searchbinarypath.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 23:37:48 by bpoetess          #+#    #+#             */
/*   Updated: 2022/07/15 01:41:33 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**getbinarypaths(char **env)
{
	char	**paths;
	char	*temp;
	int		i;

	if (!env || !*env)
		return (0);
	i = 0;
	while (env[i])
	{	
		if (!ft_strncmp(env[i], "PATH=", ft_strlen("PATH=") - 1))
		{
			temp = ft_strjoin(env[i], ":./");
			if (!temp)
				return (0);
			paths = ft_split(temp + 5, ':');
			free (temp);
			return (paths);
		}
		i++;
	}
	return (0);
}

static char	*checkbinarypaths(char *cmd, char **paths)
{
	char	*tmp;
	char	*res;
	int		i;

	i = 0;
	while (paths && paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (0);
		res = ft_strjoin(tmp, cmd);
		free (tmp);
		if (access(res, X_OK) != -1)
			return (res);
		free (res);
		i++;
	}
	return (0);
}

char	*searchbinarypath(char *cmd, char **env)
{
	char	**paths;
	char	*res;
	int		i;

	paths = getbinarypaths(env);
	if (!paths)
		return (0);
	res = checkbinarypaths(cmd, paths);
	i = 0;
	while (paths[i])
		free (paths[i++]);
	free (paths);
	return (res);
}

int	checkexecutabless(t_cmd_list *cmd_list)
{
	t_cmd	*cmd;
	char	*path;

	cmd = cmd_list->cmds;
	while (cmd)
	{
		if (!builtin_check(*cmd->cmd))
		{
			if (!ft_strchr(*cmd->cmd, '/'))
				path = searchbinarypath(*cmd->cmd, cmd_list->env);
			else
				path = ft_strdup(*cmd->cmd);
			if (!(path && access(path, X_OK) != -1))
			{
				printf("minishell: no such file or directory: %s\n", *cmd->cmd);
				if (path)
					free(path);
				return (1);
			}
			free(path);
		}
		cmd = cmd->next;
	}
	return (0);
}
