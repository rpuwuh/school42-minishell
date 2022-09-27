/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 18:47:03 by bpoetess          #+#    #+#             */
/*   Updated: 2022/09/27 22:24:23 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static	int	builtin_cd_print_error(char *error, int errorcode)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	if (errorcode == 1)
	{
		ft_putstr_fd(error, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd("No such file or directory\n", STDERR_FILENO);
		return (1);
	}
	if (errorcode == 2)
	{
		ft_putstr_fd("not a directory: ", STDERR_FILENO);
		ft_putstr_fd(error, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		return (1);
	}
	if (errorcode == 3)
		ft_putstr_fd("HOME not set\n", STDERR_FILENO);
	return (1);
}

int	builtin_cd(char *path, t_env_v *env_list)
{
	if (path)
	{
		if (access(path, F_OK))
			return (builtin_cd_print_error(path, 1));
		if (chdir(path) == -1)
			return (builtin_cd_print_error(path, 2));
		else
			return (0);
	}
	if (ft_env_get_value(env_list, "HOME"))
	{
		if (!chdir(ft_env_get_value(env_list, "HOME")))
			return (0);
		return (builtin_cd(ft_env_get_value(env_list, "HOME"), env_list));
	}
	return (builtin_cd_print_error(0, 3));
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

static int	builtin_exit_print_error(char *error, int errorcode)
{
	if (errorcode == 1)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	if (errorcode == 2)
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(error, STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		exit (255);
	}
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
		return (builtin_exit_print_error(*s, 1));
	if (!*s)
		exit (0);
	i = 0;
	while ((*s)[i] && ((*s)[i] != '0'))
		i++;
	if (ft_strlen(*s) >= 20 || (((*s)[i]) && !ft_isdigit((*s)[i])))
		builtin_exit_print_error(*s, 2);
	if ((*s)[i] == 0 || ft_isdigit((*s)[i]))
		exit(ft_atoi(*s) % 255);
	exit(255);
}
