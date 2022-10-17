/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 21:56:02 by dmillan           #+#    #+#             */
/*   Updated: 2022/10/17 20:50:19 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_env_search(t_env_v *env_v, char *name)
{
	while (env_v != NULL)
	{
		if (ft_strcmp(name, env_v->name) == 0)
			return (TRUE);
		env_v = env_v->next;
	}
	return (FALSE);
}

char	*ft_env_get_value(t_env_v *env_v, char *name)
{
	if (env_v == NULL || name == NULL)
		return (NULL);
	if (env_v != NULL && ft_strcmp(env_v->name, name) == 0)
		return (env_v->value);
	while (env_v != NULL && ft_strcmp(env_v->name, name) != 0)
		env_v = env_v->next;
	if (env_v == NULL)
		return (NULL);
	return (env_v->value);
}

void	ft_env_init(t_env_v **env, char **envp)
{
	t_env_v	*temp;
	int		i;
	char	**split_str;

	i = 0;
	*env = ft_env_create();
	temp = *env;
	while (envp[i] != NULL)
	{
		split_str = ft_split(envp[i], '=');
		if (split_str[0])
			(*env)->name = ft_strdup(split_str[0]);
		if (split_str[1])
			(*env)->value = ft_strdup(split_str[1]);
		(*env)->export = 1;
		ft_free_line(split_str);
		if (envp[i + 1] == NULL)
			break ;
		(*env)->next = ft_env_create();
		(*env) = (*env)->next;
		i++;
	}
	*env = temp;
}
