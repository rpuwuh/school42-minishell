/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 00:25:32 by bpoetess          #+#    #+#             */
/*   Updated: 2022/08/22 01:06:33 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*	writes env if command was "export"										*/

static int	writeenv(t_env_v *envin)
{
	t_env_v	*env;

	env = envin;
	while (env && env->name)
	{
		if (env->export)
			printf("declare +x %s=\"%s\"\n", env->name, env->value);
		env = env->next;
	}
	return (0);
}

/*	changes env (t_env_v) structure											*/

static void	changeenv(t_cmd_list *cmd_list, char *name, char *value)
{
	t_env_v	*env;

	env = cmd_list->env_list;
	while (env && ft_strncmp(name, env->name, ft_strlen(name)))
		env = env->next;
	if (env && !ft_strncmp(name, env->name, ft_strlen(name)) && env->value)
	{
		free (env->value);
		env->value = ft_strdup(value);
		return ;
	}
	env = cmd_list->env_list;
	while (env->next)
		env = env->next;
	env->next = (t_env_v *) malloc (sizeof(t_env_v));
	if (!env->next)
		exit (12);
	env->next->next = 0;
	env->next->export = 1;
	env->next->name = ft_strdup(name);
	env->next->value = ft_strdup(value);
}

static int	builtin_exportmainloop(char *cmd, t_cmd_list *cmd_list)
{
	char	*name;

	name = ft_substr(cmd, 0, ft_strchr(cmd, '=') - cmd);
	if (name && !envnamechecker(name))
	{
		printf("minishell: export: `%s': not a valid identifier\n", name);
		free (name);
		return (1);
	}
	else if (name)
	{
		if (ft_strchr(cmd, '='))
			changeenv(cmd_list, name, ft_strchr(cmd, '=') + 1);
		else
			changeenv(cmd_list, name, "");
	}
	free (name);
	return (0);
}

int	builtin_export(t_cmd *cmd, t_cmd_list *cmd_list)
{
	int		i;
	t_env_v	*env;
	int		result;

	if (!cmd->cmd[1])
		return (writeenv(cmd_list->env_list));
	i = 0;
	result = 0;
	while (cmd->cmd[++i])
		result = result | builtin_exportmainloop(cmd->cmd[i], cmd_list);
	i = 0;
	while (cmd_list->env && cmd_list->env[i])
		free (cmd_list->env[i++]);
	free(cmd_list->env);
	i = 0;
	env = cmd_list->env_list;
	while (env)
	{
		env = env->next;
		if (env && env->export)
			i++;
	}
	reassemble_env(cmd_list);
	builtin_env(cmd_list->env);
	return (result);
}
