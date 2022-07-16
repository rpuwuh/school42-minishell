/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 18:47:03 by bpoetess          #+#    #+#             */
/*   Updated: 2022/07/16 04:23:55 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_cd(char *path, char **env)
{
	int	i;

	if (path)
	{
		if (!chdir(path))
			return ;
		printf("minishell: cd: %s: No such file or directory\n", path);
		return ;
	}
	i = 0;
	while (env && env[i])
	{
		if (!ft_strncmp(env[i], "HOME=", ft_strlen("HOME=") - 1))
		{
			if (!chdir(env[i] + 5))
				return ;
			printf("minishell: cd: %s: No such file or directory\n", env[i]);
			return ;
		}
		i++;
	}
	printf("minishell: cd: HOME not set\n");
}

void	builtin_echo(char **args)
{
	int	i;

	if (!args || !*args)
		exit(0);
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
	exit (0);
}

void	builtin_pwd(void)
{
	char	*s;

	s = getcwd(0, 0);
	if (!s)
		exit (12);
	printf("%s\n", s);
	free (s);
	exit (0);
}

void	builtin_exit(void)
{
	printf ("exit\n");
	exit (0);
}
