/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 04:23:48 by bpoetess          #+#    #+#             */
/*   Updated: 2022/08/02 08:26:14 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	isenvnameright(char *s)
{
	int	i;

	if (!s || !*s)
		return (1);
	if (!ft_isalpha(*s) || *s != '_')
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
	while (env && ft_strncmp(name, env->name, ft_strlen(name)))
		env = env->next;
	if (!env)
		return ;
	if (!ft_strncmp(name, env->name, ft_strlen(name)))
	{
		free (env->name);
		free (env->value);
	}
	env_prev = cmd_list->env_list;
	while (env_prev->next != env)
		env_prev = env_prev->next;
	env_prev->next = env_prev->next->next;
	free(env);
}

static void	changeenvarray(char *name, char ***arr)
{
	char	**strs;
	int		i;

	if (!arr || !*arr)
		return ;
	strs = *arr;
	i = 0;
	while (strs[i] && !(!ft_strncmp(strs[i], name, ft_strlen(name) - 1)
			&& strs[i][ft_strlen(name) + 1] == '='))
		i++;
	if (!strs[i])
		return ;
	free (strs[i]);
	strs[i] = strs[i + 1];
	i++;
	while (strs[i])
	{
		strs[i] = strs[i + 1];
		i++;
	}
}

int	builtin_unset(t_cmd *cmd, t_cmd_list *cmd_list)
{
	int		result;
	int		i;

	if (!cmd->cmd[1])
		return (0);
	i = 1;
	result = 0;
	while (cmd->cmd[i])
	{
		if (!isenvnameright(cmd->cmd[i]))
		{
			printf("minishell: unset: `%s': not a valid identifier\n",
				cmd->cmd[i]);
			result = 1;
		}
		unsetfromcmd_list(cmd->cmd[i], cmd_list);
		changeenvarray(cmd->cmd[i], &cmd_list->env);
	}
	return (result);
}
