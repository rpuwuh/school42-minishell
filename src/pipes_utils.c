/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 00:22:20 by dmillan           #+#    #+#             */
/*   Updated: 2022/07/11 00:26:31 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	parent_process(int *fd, int *tmp)
{
	wait(NULL);
	close(fd[1]);
	*tmp = fd[0];
}

static void	pipe_middle(char *input, int *fd, t_env *env, int *tmp)
{
	char	**split;

	dup2(*tmp, 0);
	dup2(fd[1], 1);
	close(fd[0]);
	split = ft_split(input, ' ');
	executer(split, env);
	free(split);
	exit(1);
}

static void	pipe_last(t_token *tokens, int *fd, t_env *env, int *tmp)
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

static void	free_and_close(int *fd, char **input)
{
	close(fd[0]);
	close(fd[1]);
	ft_free_split(input);
}

t_token	*after_pipe(t_token *tokens)
{
	t_token	*tmp;
	t_token	*end;

	end = tokens;
	while (end != NULL)
	{
		if (end->type == PIPE)
			tmp = end->next;
		end = end->next;
	}
	return (tmp);
}

static void	ft_iterate_split(char **ret, t_token *tokens)
{
	t_token	*tmp;
	int		i;

	tmp = tokens;
	i = 0;
	while (tmp != NULL)
	{
		if (tmp->type == PIPE)
			tmp = tmp->next;
		ret[i] = ft_strdup(tmp->value);
		tmp = tmp->next;
		while (tmp != NULL && tmp->type != PIPE)
		{
			ret[i] = ft_append(ret[i], " ");
			ret[i] = ft_append(ret[i], tmp->value);
			tmp = tmp->next;
		}
		i++;
	}
	ret[i] = NULL;
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
	ft_iterate_split(ret, tokens);
	return (ret);
}
