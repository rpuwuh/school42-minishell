/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembleenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 01:00:03 by bpoetess          #+#    #+#             */
/*   Updated: 2022/09/07 21:27:22 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	**envreassemble(t_cmd_list *cmd_list, int i)
{
	char	*tmp;
	char	**res;
	t_env_v	*env;

	if (!cmd_list)
		return (0);
	res = (char **) malloc (sizeof (char *) * (i + 1));
	if (!res)
		return (0);
	i = 0;
	env = cmd_list->env_list;
	while (env)
	{
		if (env->export)
		{
			tmp = ft_strjoin(ft_strdup(env->name), "=");
			if (env->value)
				res[i++] = ft_strjoin (tmp, env->value);
			else
				res[i++] = ft_strjoin (tmp, ft_strdup(""));
		}
		env = env->next;
	}
	res[i] = (char *) 0;
	return (res);
}

char	**reassemble_env(t_cmd_list *cmd_list)
{
	int		i;
	char	**env;
	t_env_v	*env_list;

	i = 0;
	env_list = cmd_list->env_list;
	while (env_list)
	{
		if (env_list->export)
			i++;
		env_list = env_list->next;
	}
	env = envreassemble(cmd_list, i);
	return (env);
}

t_cmd_list	*ft_cmd_init(t_cmd_list	*cmd_list, t_env_v	**env)
{
	cmd_list->env_list = *env;
	cmd_list->cmds = NULL;
	return (cmd_list);
}
