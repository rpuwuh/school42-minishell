/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 23:14:08 by dmillan           #+#    #+#             */
/*   Updated: 2022/08/08 23:53:02 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_get_fd(int *fd_list)
{
	int	i;

	i = 0;
	while (fd_list[i] != -1)
	{
		if (fd_list[i + 1] == -1)
			return (fd_list[i]);
		close(fd_list[i]);
		i++;
	}
	return (-1);
}

void	ft_add_cmd(t_cmd_list *cmd_list,
			char **pipe_part, int fd_in, int fd_out)
{
	t_cmd	*cmd_new;
	t_cmd	*cmd_temp;

	cmd_new = (t_cmd *)malloc(sizeof(t_cmd));
	cmd_new->cmd = pipe_part;
	cmd_new->fd_in = fd_in;
	cmd_new->fd_out = fd_out;
	cmd_new->pid = 0;
	if (!cmd_list->cmds)
		cmd_list->cmds = NULL;
	cmd_temp = cmd_list->cmds;
	cmd_new->next = cmd_temp;
	cmd_list->cmds = cmd_new;
}
void	ft_cmdlist_free(t_cmd_list *cmd_list)
{
	t_cmd	*tmp;

	tmp = cmd_list->cmds;
	while (tmp != NULL)
	{
		tmp = cmd_list->cmds->next;
		int i = 0;
		while (cmd_list->cmds->cmd[i] != NULL)
			free(cmd_list->cmds->cmd[i++]);
		cmd_list->cmds = tmp;
	}
	//free(cmd_list);
}

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

	tmp = *env;
	count = ft_count_env(tmp);
	envp = (char **)malloc(count * sizeof(char *));
	i = 0;
	tmp = *env;
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
