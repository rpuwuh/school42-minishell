/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 18:47:03 by bpoetess          #+#    #+#             */
/*   Updated: 2022/08/02 04:33:09 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_cd(char *path, char **env)
{
	int	i;

	if (path)
	{
		if (!chdir(path))
			return (0);
		printf("minishell: cd: %s: No such file or directory\n", path);
		return (1);
	}
	i = 0;
	while (env && env[i])
	{
		if (!ft_strncmp(env[i], "HOME=", ft_strlen("HOME=") - 1))
		{
			if (!chdir(env[i] + 5))
				return (0);
			printf("minishell: cd: %s: No such file or directory\n", env[i]);
			return (1);
		}
		i++;
	}
	printf("minishell: cd: HOME not set\n");
	return (1);
}

int	builtin_echo(char **args)
{
	int	i;

	if (!args || !*args)
		return (0);
	i = 0;
	if (!ft_strncmp(*args, "-n", ft_strlen ("-n")))
		i++;
	while (args[i])
	{
		printf("%s", args[i]);
		i++;
		if (args[i])
			printf (" ");
	}
	if (ft_strncmp(*args, "-n", ft_strlen ("-n")))
		printf("\n");
	return (0);
}

int	builtin_pwd(void)
{
	char	*s;

	s = getcwd(0, 0);
	if (!s)
		return (12);
	printf("%s\n", s);
	free (s);
	return (0);
}

int	builtin_exit(char **s)
{
	int	i;

	printf ("exit\n");
	i = 0;
	while (s && s[i])
		i++;
	if (i > 1)
	{
		printf("minishell: exit: too many arguments\n");
		return (1);
	}
	if (!*s)
		exit (0);
	i = 0;
	while ((*s)[i] && ((*s)[i] != '0'))
		i++;
	if (ft_strlen(*s) >= 20 || (((*s)[i]) && !ft_isdigit((*s)[i])))
	{
		printf("minishell: exit: %s: numeric argument required\n", *s);
		exit (255);
	}
	if ((*s)[i] == 0 || ft_isdigit((*s)[i]))
		exit(ft_atoi(*s) % 255);
	exit(255);
}
