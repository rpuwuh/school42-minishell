/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 21:15:52 by dmillan           #+#    #+#             */
/*   Updated: 2022/07/09 23:48:34 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_shell_init(t_env_v	**env, char **envp, char *prompt)
{
	char	*env_value;

	ft_env_init(env, envp);
	env_value = ft_env_get_value(*env, "SHLVL");
	if (env_value)
	{
		env_value = ft_itoa(ft_atoi(env_value) + 1);
		ft_env_replace(env, "SHLVL", env_value, 1);
		free(env_value);
	}
	env_value = getcwd(NULL, 1000);
	env_value = ft_strjoin(env_value, "/minishell");
	ft_env_replace(env, "SHELL", env_value, 1);
	free(env_value);
	prompt = ft_get_prompt(env);
	ft_env_add(env, ft_strdup("?"), ft_strdup("0"), FALSE);
	return (0);
}
