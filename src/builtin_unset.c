/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 04:23:48 by bpoetess          #+#    #+#             */
/*   Updated: 2022/10/17 20:51:29 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	builtin_env(t_env_v *env_list)
{
	t_env_v	*env_temp;

	env_temp = env_list;
	while (env_temp)
		env_temp = env_temp->next;
	return (0);
}

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
		cmd_list->env_list = cmd_list->env_list->next;
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
		if (!envnamechecker(cmd->cmd[i]))
		{
			ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
			ft_putstr_fd(cmd->cmd[i], STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			result = 1;
		}
		unsetfromcmd_list(cmd->cmd[i], cmd_list);
	}
	return (result);
}
