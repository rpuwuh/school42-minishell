/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 00:19:34 by dmillan           #+#    #+#             */
/*   Updated: 2022/07/15 02:19:11 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_pipe_process(t_token *tokens_part, t_cmd_list *cmd_list)
{
	char	**pipe_part;

	if (ft_redirections_exist(tokens_part) == TRUE)
		ft_redirections_parse(tokens_part, cmd_list);
	else
	{
		pipe_part = ft_tokens_convert(tokens_part);
		ft_add_cmd(cmd_list, pipe_part, 0, 1);
		ft_free_line(pipe_part);
	}
}

t_token	*ft_pipe_part_token(t_token *tokens, int *count_pipes)
{
	t_token	*token_part;
	t_token	*tmp;
	int		i;

	tmp = tokens;
	token_part = tmp;
	i = 0;
	while (tmp != NULL && tmp->next != NULL)
	{
		if (tmp->type == PIPE)
		{
			if (*count_pipes == i + 1)
				token_part = tmp;
			i++;
		}
		else if (tmp->next->type == PIPE && *count_pipes == i)
		{
			token_part->next = NULL;
			*count_pipes = *count_pipes + 1;
			return (token_part);
		}
		tmp = tmp->next;
		token_part = token_part->next;
	}
	return (token_part);
}

void	ft_pipe_parse(t_token *tokens, t_cmd_list *cmd_list)
{
	t_token	*tmp;
	int		count_pipe;
	t_token	*tokens_part;
	int		i;

	tmp = tokens;
	i = 0;
	while (tmp != NULL)
	{
		if (tmp->type == PIPE)
		{
			tokens_part = ft_pipe_part_token(tokens, &count_pipe);
			if (tokens_part->type == PIPE)
				tokens_part = tokens_part->next;
			ft_pipe_process(tokens_part, cmd_list);
			count_pipe++;
		}
		tmp = tmp->next;
	}
	ft_executer(cmd_list);
}
