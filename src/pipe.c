/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 00:19:34 by dmillan           #+#    #+#             */
/*   Updated: 2022/07/11 00:37:55 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_parent_process(int *fd, int *tmp)
{
	wait(NULL);
	close(fd[1]);
	*tmp = fd[0];
}

static void	ft_pipe_process(char *input, int *fd,
	t_env_v **env, int *tmp, char	**envp)
{
	char	**split;

	dup2(*tmp, 0);
	dup2(fd[1], 1);
	close(fd[0]);
	split = ft_split(input, ' ');
	executer(split, env, envp);
	free(split);
	exit(1);
}

static void	ft_pipe_last_process(t_token *tokens, int *fd, t_env_v **env, int *tmp)
{
	char	**split;
	t_token	*tmp_tokens;

	dup2(*tmp, 0);
	close(fd[0]);
	tmp_tokens = after_pipe(tokens);
	if (has_redirections(tmp_tokens) == true)
		parse_redirections(env, tmp_tokens);
	else
	{
		split = convert_tokens(tmp_tokens);
		executer(split, env);
		ft_free_split(split);
	}
	exit(1);
}

char	**ft_tokens_split(t_token *tokens)
{
	char	**ret;
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
	ret = ft_calloc(i + 1, sizeof(char *));
	if (ret == NULL)
		return (NULL);
	iterate_split(ret, tokens);
	return (ret);
}

void	ft_pipe_parse(t_token *tokens, t_env_v **env, int i, char	**envp)
{
	int		fd[2];
	int		tmp;
	pid_t	pid;
	char	**input;

	tmp = 0;
	input = ft_tokens_split(tokens);
	while (input[i] != NULL)
	{
		if (pipe(fd) == -1)
			exit(EXIT_FAILURE);
		pid = fork();
		if (pid == 0)
		{
			if (input[i + 1] == NULL)
				ft_pipe_last_process(tokens, fd, env, &tmp);
			else
				ft_pipe_process(input[i], fd, envp, &tmp);
		}
		else
			parent_process(fd, &tmp);
		i++;
	}
	free_and_close(fd, input);
}
