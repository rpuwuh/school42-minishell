/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_choose.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 00:10:38 by bpoetess          #+#    #+#             */
/*   Updated: 2022/10/18 10:29:21 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	count_cmds(t_cmd_list *cmd_list)
{
	int		i;
	t_cmd	*cmd;

	i = 0;
	cmd = cmd_list->cmds;
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}

int	builtin_check(char **cmd)
{
	if (!ft_strncmp(*cmd, "cd", ft_strlen("cd") + 1)
		|| (!ft_strncmp(*cmd, "export", ft_strlen("export") + 1) && (cmd[1]))
		|| !ft_strncmp(*cmd, "unset", ft_strlen("unset") + 1)
		|| !ft_strncmp(*cmd, "exit", ft_strlen("exit") + 1))
		return (1);
	if (!ft_strncmp(*cmd, "pwd", ft_strlen("pwd") + 1)
		|| !ft_strncmp(*cmd, "env", ft_strlen("env") + 1)
		|| (!ft_strncmp(*cmd, "export", ft_strlen("env") + 1) && (!cmd[1]))
		|| !ft_strncmp(*cmd, "echo", ft_strlen("echo") + 1))
		return (2);
	return (0);
}

int	choosefunc(t_cmd *cmd, t_cmd_list *cmd_list)
{
	if (!ft_strncmp(cmd->cmd[0], "pwd", ft_strlen("pwd")))
		return (builtin_pwd());
	if (!ft_strncmp(cmd->cmd[0], "echo", ft_strlen("echo")))
		return (builtin_echo(&(cmd->cmd)[1]));
	if (!ft_strncmp(cmd->cmd[0], "env", ft_strlen("env")))
		return (builtin_env(cmd_list->env_list));
	if (!ft_strncmp(cmd->cmd[0], "cd", ft_strlen("cd")))
		return (builtin_cd(cmd->cmd[1], cmd_list->env_list));
	if (!ft_strncmp(cmd->cmd[0], "exit", ft_strlen("exit"))
		&& count_cmds(cmd_list) == 1)
		return (builtin_exit(cmd->cmd + 1));
	if (!ft_strncmp(cmd->cmd[0], "unset", ft_strlen("unset")))
		return (builtin_unset(cmd, cmd_list));
	if (!ft_strncmp(cmd->cmd[0], "export", ft_strlen("export")))
		return (builtin_export(cmd, cmd_list));
	return (1);
}
