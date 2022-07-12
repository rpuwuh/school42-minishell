/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 23:14:08 by dmillan           #+#    #+#             */
/*   Updated: 2022/07/13 00:30:27 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_count_env(t_env_v	*tmp)
{
	int	i;

	i = 0;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

char	**ft_collect_envp(t_env_v **env)
{
	t_env_v	*tmp;
	int		count;
	int		i;
	char	**envp;

	tmp = *env_v;
	count = ft_count_env(tmp);
	envp = (char **)malloc(count * sizeof(char *));
	i = 0;
	tmp = *env_v;
	while (tmp != NULL)
	{
		envp[i] = ft_strdup(tmp->name);
		envp[i] = ft_strjoin(envp[i], "=");
		envp[i] = ft_strjoin(envp[i], tmp->value);
		tmp = tmp->next;
		i++;
	}
	return (envp);
}
