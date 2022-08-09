/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searchbinarypath.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 23:37:48 by bpoetess          #+#    #+#             */
/*   Updated: 2022/08/10 00:32:25 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	**getbinarypaths(char **env)
{
	char	**paths;
	int		i;

	if (!env || !*env)
		return (0);
	i = 0;
	while (env[i])
	{	
		if (!ft_strncmp(env[i], "PATH=", ft_strlen("PATH=") - 1))
		{
			paths = ft_split(env[i] + 5, ':');
			return (paths);
		}
		i++;
	}
	paths = (char **) malloc (sizeof (char *) * 2);
	paths [0] = ft_strdup(".");
	paths [1] = 0;
	return (paths);
}

static char	*choosebinarypath(char **oldfullpath, char *newpath, char *cmd)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(newpath, "/");
	if (!tmp)
		return (0);
	res = ft_strjoin(tmp, cmd);
	free (tmp);
	if (access(res, F_OK) != -1)
	{
		if (oldfullpath)
			free (*oldfullpath);
		return (res);
	}
	else
		free (res);
	return (0);
}

static char	*checkbinarypaths(char *cmd, char **paths)
{
	char	*res;
	int		i;

	i = 0;
	res = 0;
	while (paths && paths[i])
	{
		res = choosebinarypath(&res, paths[i], cmd);
		if (access(res, X_OK) != -1)
			return (res);
		i++;
	}
	return (res);
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
