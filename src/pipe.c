/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 00:19:34 by dmillan           #+#    #+#             */
/*   Updated: 2022/07/13 00:27:03 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_parent_process(int *fd, int *tmp)
{
	wait(NULL);
	close(fd[1]);
	*tmp = fd[0];
}

static void	ft_pipe_process(t_token *tokens, int *fd, t_env_v **env, int *tmp)
{
	char	**pipe_part;
	t_token	*tmp_tokens;
	char	**envp;

	dup2(*tmp, 0);
	dup2(fd[1], 1);
	close(fd[0]);
	if (ft_redirections_exist(tokens) == TRUE)
		parse_redirections(env, tokens);
	else
	{
		pipe_part = ft_convert_tokens(tokens);
		envp = ft_collect_envp(t_env_v **env);
		executer(pipe_part, env, envp);
		ft_free_line(split);
	}
	exit(TRUE);
}

char	**ft_tokens_join(t_token *tokens)
{
	char	**pipe_parts;
	t_token	*tmp;
	int		i;

	tmp = tokens;
	i = 1;
	while (tmp != NULL)
	{
		if (tmp->type == PIPE)
		{
			i++;
			tmp = tmp->next;
		}
		tmp = tmp->next;
	}
	pipe_parts = (char **)malloc((i + 1) * sizeof(char *));
	if (pipe_parts == NULL)
		return (NULL);
	ft_iterate_join(pipe_parts, tokens);
	return (pipe_parts);
}

void	ft_pipe_parse(t_token *tokens, t_env_v **env, int i, char	**envp)
{
	int		fd[2];
	int		tmp;
	pid_t	pid;
	char	**input;

	tmp = 0;
	input = ft_tokens_join(tokens);
	while (input[i] != NULL)
	{
		if (pipe(fd) == -1)
			exit(EXIT_FAILURE);
		pid = fork();
		if (pid == 0)
			ft_pipe_process(input[i], fd, env, &tmp);
		else
			ft_parent_process(fd, &tmp);
		i++;
	}
	ft_free_and_close(fd, input);
}
