/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 23:14:08 by dmillan           #+#    #+#             */
/*   Updated: 2022/08/14 21:52:11 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_get_fd_in(int *fd_list)
{
	int	i;

	i = 0;
	{
		while (fd_list[i] != -1)
		{
			if (fd_list[i + 1] == -1)
			{
				printf("fd_in = %d\n", fd_list[i]);
				return (fd_list[i]);
			}
			close(fd_list[i]);
			i++;
		}
	}
	printf("fd_in = 0\n");
	return (0);
}

int	ft_get_fd_out(int *fd_list)
{
	int	i;

	i = 1;
	while (fd_list[i] != -1)
	{
		if (fd_list[i + 1] == -1)
		{
			printf("fd_out = %d\n", fd_list[i]);
			return (fd_list[i]);
		}
		close(fd_list[i]);
		i++;
	}
	printf("fd_out = 1\n");
	return (1);
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
