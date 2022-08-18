/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 00:19:34 by dmillan           #+#    #+#             */
/*   Updated: 2022/08/18 00:16:57 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_pipe_process(t_token **tokens_part, t_cmd_list *cmd_list)
{
	char	**pipe_part;

	if (ft_redirections_exist(tokens_part) == TRUE)
		ft_redirections_parse(tokens_part, cmd_list);
	else
	{
		pipe_part = NULL;
		pipe_part = ft_tokens_convert(tokens_part);
		ft_add_cmd(cmd_list, pipe_part, 0, 1);
		//ft_free_line(pipe_part);
	}
}

void	ft_pipe_parse(t_token **tokens, t_cmd_list *cmd_list)
{
	t_token	*tokens_part;
	t_token	*tmp;

	tmp = *tokens;
	tokens_part = NULL;
	printf("into pipe\n");
	while (tmp != NULL)
	{
		ft_token_add(&tokens_part, tmp);
		if (tmp->next && tmp->next->type == PIPE)
		{
			ft_pipe_process(&tokens_part, cmd_list);
			tokens_part = NULL;
			tmp = tmp->next;
		}
		else if (!tmp->next)
		{
			ft_pipe_process(&tokens_part, cmd_list);
			break ;
		}
		tmp = tmp->next;
	}
	//free(tokens_part);
}
