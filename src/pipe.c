/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 00:19:34 by dmillan           #+#    #+#             */
/*   Updated: 2022/07/16 02:45:55 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_pipe_process(t_token *tokens_part, t_cmd_list *cmd_list)
{
	char	**pipe_part;
	int i;

	if (ft_redirections_exist(&tokens_part) == TRUE)
		ft_redirections_parse(tokens_part, cmd_list);
	else
	{
		printf("token_part = %s\n", "check2");
		pipe_part = ft_tokens_convert(tokens_part);
		i = 0;
		while (pipe_part[i] != '\0')
			printf("command_pipe_i = %s\n", pipe_part[i++]);
		ft_add_cmd(cmd_list, pipe_part, 0, 1);
		ft_free_line(pipe_part);
	}
}

void	ft_pipe_parse(t_token *tokens, t_cmd_list *cmd_list)
{
	t_token	*tokens_part;
	t_token	*tmp;
	t_token *tmp2;

	tmp = tokens;
	printf("token_tmp = %s\n", tmp->value);
	printf("token_tokens = %s\n", tokens->value);
	tokens_part = NULL;
	while (tmp != NULL)
	{
		ft_token_add(tokens_part, tmp);
		tmp2 = tokens_part;
		//printf("token_part = %s\n", tmp2->value);
		if(tmp->next != NULL && tmp->next->type == PIPE)
		{
			printf("token_part = %s\n", "check");
			ft_pipe_process(tokens_part, cmd_list);
			//free(tokens_part);
			tokens_part = ft_tokens_init();
			tmp = tmp->next;
			printf("token_part = %s\n", "check");
		}
		tmp = tmp->next;
	}
	ft_token_add(tokens_part, tmp);
	tokens_part->next = NULL;
	ft_pipe_process(tokens_part, cmd_list);
	free(tokens_part);
	ft_executer(cmd_list);
}
