/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 00:22:20 by dmillan           #+#    #+#             */
/*   Updated: 2022/07/13 00:26:30 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**ft_tokens_convert(t_token *tokens)
{
	char	**token_join;
	t_token	*tmp;
	int		i;

	tmp = tokens;
	i = 0;
	while (tmp != NULL && tmp->type == NONE)
	{
		tmp = tmp->next;
		i++;
	}
	token_join = (char **)malloc((i + 1) * sizeof(char *));
	if (token_join == NULL)
		return (NULL);
	tmp = tokens;
	i = 0;
	while (tmp != NULL && tmp->type == NONE)
	{
		token_join[i] = ft_strdup(tmp->value);
		tmp = tmp->next;
		i++;
	}
	token_join[i] = NULL;
	return (ret);
}

static void	ft_free_and_close(int *fd, char **input)
{
	close(fd[0]);
	close(fd[1]);
	ft_free_line(input);
}

static void	ft_iterate_join(char **pipe_part, t_token *tokens)
{
	t_token	*tmp;
	int		i;

	tmp = tokens;
	i = 0;
	while (tmp != NULL)
	{
		if (tmp->type == PIPE)
			tmp = tmp->next;
		pipe_part[i] = ft_strdup(tmp->value);
		tmp = tmp->next;
		while (tmp != NULL && tmp->type != PIPE)
		{
			pipe_part[i] = ft_strjoin(pipe_part[i], " ");
			pipe_part[i] = ft_strjoin(pipe_part[i], tmp->value);
			tmp = tmp->next;
		}
		i++;
	}
	pipe_part[i] = NULL;
}
