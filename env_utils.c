/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 21:56:02 by dmillan           #+#    #+#             */
/*   Updated: 2022/07/06 00:09:15 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_exists(char *name)
{
	int		i;
	char	*key;

	i = 0;
	while (g_minishell.env[i] != NULL)
	{
		key = env_key(g_minishell.env[i]);
		if (key != NULL)
		{
			if (ft_strncmp(key, name, ft_strlen(key) + 1) == 0)
			{	
				free(key);
				return (i);
			}
			free(key);
		}
		i++;
	}
	return (-1);
}

char	*env_get(char *name, int i, char *key, char *pwd)
{
/*	if (ft_strncmp("?", name, 2) == 0)
		return (ft_itoa(g_minishell.return_value));
	if (ft_strncmp("PWD", name, 4) == 0)
	{
		pwd = getcwd(NULL, 1000);
		if (g_minishell.double_slash == 1)
			return (ft_strjoin("/", pwd));
		return (pwd);
	}
	if (ft_isdigit(name[0]) && ft_strlen(name) > 1)
		return (ft_strdup(name + 1)); */
	while (g_minishell.env[i] != NULL)
	{
		key = env_key(g_minishell.env[i]);
		if (key != NULL)
		{
			if (ft_strncmp(key, name, ft_strlen(key) + 1) == 0)
			{
				return (env_value(g_minishell.env[i]));
			}
			free(key);
		}
		i++;
	}
	return (ft_strdup(""));
}

int	env_len(void)
{
	int		i;

	i = 0;
	while (g_minishell.env[i])
		i++;
	return (i);
}

static void	env_set2(char *n, char *v)
{
	free(n);
	free(v);
	free(g_minishell.env);
}

static void	env_set3(char **tmp, char *final, int i)
{
	tmp[i] = final;
	tmp[i + 1] = NULL;
	g_minishell.env = tmp;
}

int	env_set(char *name, char *value, int i)
{
	char	**tmp;
	char	*n;
	char	*v;
	char	*final;

	if (env_exists(name))
		if (env_unset(name, 0, 0, NULL) == -1)
			return (-1);
	tmp = malloc(sizeof(char *) * (env_len() + 2));
	if (tmp == NULL)
		return (-1);
	while (i < env_len())
	{
		tmp[i] = g_shell.envp[i];
		i++;
	}
	n = ft_strjoin(name, "=");
	v = remove_dquote(value);
	if (v == NULL)
		final = ft_strdup(n);
	else
		final = ft_strjoin(n, v);
	env_set2(n, v);
	env_set3(tmp, final, i);
	return (0);
}
