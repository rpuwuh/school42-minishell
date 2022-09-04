/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembleenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 01:00:03 by bpoetess          #+#    #+#             */
/*   Updated: 2022/09/03 19:45:23 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	envreassemble(t_cmd_list *cmd_list, int i)
{
	char	*tmp;
	t_env_v	*env;

	cmd_list->env = (char **) malloc (sizeof (char *) * (i + 2));
	if (!cmd_list)
		return ;
	i = 0;
	env = cmd_list->env_list;
	while (env)
	{
		if (env->export)
		{
			tmp = ft_strjoin(ft_strdup(env->name), "=");
			if (env->value)
				cmd_list->env[i] = ft_strjoin (tmp, env->value);
			else
				cmd_list->env[i] = ft_strjoin (tmp, ft_strdup(""));
			i++;
		}
		env = env->next;
	}
	(cmd_list->env)[i] = (char *) NULL;
	(cmd_list->env)[i + 1] = (char *) NULL;
}

void	reassemble_env(t_cmd_list *cmd_list)
{
	int		i;
	t_env_v	*env_list;

	i = 0;
	while (cmd_list->env != 0 && cmd_list->env[i] != 0)
	{
		free (cmd_list->env[i]);
		(cmd_list->env)[i++] = 0;
	}
	if (cmd_list->env)
		free (cmd_list->env);
	cmd_list->env = 0;
	i = 0;
	env_list = cmd_list->env_list;
	while (env_list)
	{
		env_list = env_list->next;
		if (env_list && env_list->export)
			i++;
	}
	envreassemble(cmd_list, i);
	return ;
}

t_cmd_list	*ft_cmd_init(t_cmd_list	*cmd_list, t_env_v	**env)
{
	cmd_list->env_list = *env;
	reassemble_env(cmd_list);
	cmd_list->cmds = NULL;
	return (cmd_list);
}
