/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 21:15:52 by dmillan           #+#    #+#             */
/*   Updated: 2022/07/08 17:56:58 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*prompt_set(t_env_v	**env)
{
	if (env_get_value() != NULL)
		prompt = 
	else
		prompt = BLUE"minishell$ "RESETCOLOR;
}

int	shell_init(t_env_v	**env, char **envp, char *prompt)
{
	char	*env_value;

	env_init(env, envp);
	env_value = env_get_value(*env, "SHLVL");
	if (env_value)
	{
		env_value = ft_itoa(ft_atoi(env_value) + 1);
		env_replace(env, "SHLVL", env_value, 1);
		free(env_value);
	}
	env_value = getcwd(NULL, 1000);
	env_value = ft_strjoinfree(env_value, "/minishell", 1);
	env_replace(env, "SHELL", env_value, 1);
	free(env_value);
	prompt = prompt_set(env);
	return (0);
}

