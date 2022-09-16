/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 18:47:03 by bpoetess          #+#    #+#             */
/*   Updated: 2022/09/12 09:12:20 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	builtin_cd(char *path, t_env_v *env_list)
{
	if (path)
	{
		if (access(path, F_OK))
			return (1 & (1 | printf("minishell: cd: %s: %s", path,
						"No such file or directory\n")));
		if (!chdir(path))
			return (0);
		printf("minishell: cd: not a directory: %s\n", path);
		return (1);
	}
	if (ft_env_get_value(env_list, "HOME"))
	{
		if (!chdir(ft_env_get_value(env_list, "HOME")))
			return (0);
		return (builtin_cd(ft_env_get_value(env_list, "HOME"), env_list));
	}
	printf("minishell: cd: HOME not set\n");
	return (1);
}

int	builtin_echo(char **args)
{
	int	i;

	if (!args)
		return (0);
	else if (!*args)
		return (printf("\n") & 0);
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

int	builtin_env(t_env_v *env_list)
{
	t_env_v	*env_temp;

	env_temp = env_list;
	while (env_temp)
	{
		printf("%s=%s\n", env_temp->name, env_temp->value);
		env_temp = env_temp->next;
	}
	return (0);
}
