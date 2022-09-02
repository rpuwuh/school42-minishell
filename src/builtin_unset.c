/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 04:23:48 by bpoetess          #+#    #+#             */
/*   Updated: 2022/09/02 20:36:22 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	envnamechecker(char *s)
{
	int	i;

	if (!s || !*s)
		return (1);
	if (!(ft_isalpha(*s) || *s == '_'))
		return (0);
	i = 0;
	while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
		i++;
	if (!s[i])
		return (1);
	return (0);
}

static void	unsetfromcmd_list(char *name, t_cmd_list *cmd_list)
{
	t_env_v	*env;
	t_env_v	*env_prev;

	env = cmd_list->env_list;
	while (env && ft_strncmp(name, env->name, ft_strlen(name) + 1))
		env = env->next;
	if (!env)
		return ;
	if (!ft_strncmp(name, env->name, ft_strlen(name) + 1))
	{
		free (env->name);
		free (env->value);
	}
	if (env && env == cmd_list->env_list)
	{
		cmd_list->env_list = env->next;
		free (env);
		return ;
	}
	env_prev = cmd_list->env_list;
	while (env_prev->next != env)
		env_prev = env_prev->next;
	env_prev->next = env_prev->next->next;
	free(env);
}

int	builtin_unset(t_cmd *cmd, t_cmd_list *cmd_list)
{
	int		result;
	int		i;

	if (!cmd->cmd[1])
		return (0);
	i = 0;
	result = 0;
	while (cmd->cmd[++i])
	{
		printf("name = %s\n", cmd->cmd[i]);
		if (!envnamechecker(cmd->cmd[i]))
		{
			printf("minishell: unset: `%s': not a valid identifier\n",
				cmd->cmd[i]);
			result = 1;
		}
		unsetfromcmd_list(cmd->cmd[i], cmd_list);
	}
	reassemble_env(cmd_list);
	return (result);
}
