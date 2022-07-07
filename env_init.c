/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 21:56:02 by dmillan           #+#    #+#             */
/*   Updated: 2022/07/08 00:27:42 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_search(t_env_v *env_v, char *name)
{
	while (env_v != NULL)
	{
		if (ft_strcmp(name, env_v->name) == 0)
			return (TRUE);
		env_v = env_v->next;
	}
	return (FALSE);
}

char	*env_get_value(t_env_v *env_v, char *name)
{
	if (env_v != NULL && ft_strcmp(env_v->name, name) == 0)
		return (env_v->value);
	while (env_v != NULL && ft_strcmp(env_v->name, name) != 0)
		env_v = env_v->next;
	if (env_v == NULL)
		return (NULL);
	return (env_v->value);
}

void	env_init(t_env_v **env, char **envp)
{
	t_env_v	*temp;
	int		i;
	char	**split_str;

	i = 0;
	*env = env_create();
	temp = *env;
	while (envp[i] != NULL)
	{
		split_str = ft_split(envp[i], '=');
		(*env)->name = ft_strdup(split_string[0]);
		(*env)->value = ft_strdup(split_string[1]);
		(*env)->export = 1;
		ft_free_split(split_str);
		if (envp[i + 1] == NULL)
			break ;
		(*env)->next = env_create();
		(*env) = (*env)->next;
		i++;
	}
	*env = temp;
}