/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 00:19:34 by dmillan           #+#    #+#             */
/*   Updated: 2022/10/19 21:44:39 by bpoetess         ###   ########.fr       */
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
		printf("pipe_check_pass\n");
		pipe_part = NULL;
		pipe_part = ft_tokens_convert(tokens_part);
		int i = 0;
		while (pipe_part[i])
			printf("pipe_part_i = %s\n", pipe_part[i++]);
		ft_add_cmd(cmd_list, pipe_part, 0, 1);
		ft_free_line(pipe_part);
	}
}

void	ft_pipe_parse(t_token *tokens, t_cmd_list *cmd_list)
{
	t_token	*tokens_part;
	t_token	*tmp;
	t_token	*tmp_prev;

	tmp = tokens;
	tokens_part = NULL;
	while (tmp != NULL)
	{
		if (tmp->type != PIPE)
			ft_token_add(&tokens_part, tmp);
		if (tmp->next && tmp->next->type == PIPE)
		{
			ft_pipe_process(tokens_part, cmd_list);
			tokens_part = NULL;
		}
		else if (!tmp->next)
		{
			ft_pipe_process(tokens_part, cmd_list);
			break ;
		}
		tmp_prev = tmp;
		tmp = tmp->next;
		printf("tmp_prev_val = %s\n", tmp_prev->value);
		if (tmp_prev)
			free(tmp_prev);
	}
	//ft_tokens_free(tmp2);
}
