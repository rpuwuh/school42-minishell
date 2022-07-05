/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 21:15:52 by dmillan           #+#    #+#             */
/*   Updated: 2022/07/06 00:09:54 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_free(void)
{
	int	i;

	i = 0;
	while (g_minishell.env[i] != NULL)
		free(g_minishell.env[i++]);
	if (g_minishell.env)
		free(g_minishell.env);
	return (0);
}

int	env_init(char **envp)
{
	int		i;

	i = 0;
	while (envp[i] != NULL)
		i++;
	g_shell.envp = malloc((i + 1) * sizeof(char *));
	if (g_shell.envp == NULL)
		return (-1);
	i = 0;
	while (envp[i] != NULL)
	{
		g_shell.envp[i] = ft_strdup(envp[i]);
		if (g_shell.envp[i] == NULL)
			return (env_free());
		i++;
	}
	g_minishell.env[i] = NULL;
	//env_unset("P_PWD", 0, 0, NULL);
	return (0);
}

int	shell_init(char **envp)
{
	char	*env_value;

	env_init(envp);
	env_value = env_get("SHLVL", 0, NULL, NULL);
	if (env_value)
	{
		env_value = ft_itoa(ft_atoi(env_value) + 1);
		env_set("SHLVL", env_value, 0, NULL);
		free(key);
	}
	env_value = getcwd(NULL, 1000);
	env_value = ft_strjoinfree(env_value, "/minishell", 1);
	env_set("SHELL", env_value, 0, NULL);
	free(env_value);
	g_shell.value = 0;
	g_shell.fd_input = dup(STDIN_FILENO);
	g_shell.fd_output = dup(STDOUT_FILENO);
	g_shell.original = NULL;
	g_shell.input_type = 0;
	g_shell.cmd_token = NULL;
	g_shell.delim = NULL;
	g_shell.delim_str = NULL;
	return (0);
}

int	shell_clear(void)
{
	g_shell.tokens = NULL;
	g_shell.cmd_token = NULL;
	g_shell.original = NULL;
	if (g_shell.delim_str == NULL)
	{
		g_shell.delim_str = (char *)malloc(sizeof(char));
		if (!g_shell.delim_str)
			return (1);
		g_minishell.delim_str[0] = '\0';
	}
	return (0);
}
