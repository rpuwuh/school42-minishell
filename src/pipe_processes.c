/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_processes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 23:36:29 by dmillan           #+#    #+#             */
/*   Updated: 2022/07/13 00:30:22 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_parent_process(int *fd, int *tmp)
{
	wait(NULL);
	close(fd[1]);
	*tmp = fd[0];
}

static void	ft_pipe_process(t_token *tokens, int *fd, t_env_v **env, int *tmp)
{
	char	**split;
	t_token	*tmp_tokens;
	char	**envp;

	dup2(*tmp, 0);
	dup2(fd[1], 1);
	close(fd[0]);
	if (has_redirections(tokens) == TRUE)
		parse_redirections(env, tmp_tokens);
	else
	{
		split = ft_convert_tokens(tmp_tokens);
		envp = ft_collect_envp(t_env_v **env);
		executer(split, env, envp);
		ft_free_line(split);
	}
	exit(TRUE);
}
