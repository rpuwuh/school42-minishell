/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 04:23:48 by bpoetess          #+#    #+#             */
/*   Updated: 2022/08/14 22:06:31 by bpoetess         ###   ########.fr       */
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
	while (env && ft_strncmp(name, env->name, ft_strlen(name)))
		env = env->next;
	if (!env)
		return ;
	if (!ft_strncmp(name, env->name, ft_strlen(name)))
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

static void	changeenvarray(char *name, char ***arr)
{
	char	**strs;
	int		i;

	if (!arr || !*arr)
		return ;
	strs = *arr;
	i = 0;
	while (strs[i] && !(!ft_strncmp(strs[i], name, ft_strlen(name) - 1)
			&& strs[i][ft_strlen(name)] == '='))
		i++;
	if (!strs[i])
		return ;
	printf("%s\n", strs[i]);
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
		changeenvarray(cmd->cmd[i], &cmd_list->env);
		printf("\n");
		i = 0;
		while (cmd_list->env && cmd_list->env[i])
			printf("%s\n", cmd_list->env[i++]);
	}
	return (result);
}
