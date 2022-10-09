/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 00:41:41 by dmillan           #+#    #+#             */
/*   Updated: 2022/10/10 00:22:58 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_redirections_count(t_token *tokens, int type_a, int type_b)
{
	int		i;
	t_token	*tmp;

	tmp = tokens;
	i = 0;
	while (tmp != NULL)
	{
		if ((int)tmp->type == type_a || (int)tmp->type == type_b)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

int	ft_fd_list_check(t_token *tokens,
		int type_a, int type_b, int *fd_list)
{
	int		i;
	t_token	*tmp;

	tmp = tokens;
	i = 0;
	while (tmp != NULL)
	{
		printf ("check4-1: %s\n", tmp->value);
		if ((int)tmp->type == type_a || (int)tmp->type == type_b)
		{
			if (tmp->type == HEREDOC)
				fd_list[i] = here_doc_fd(tmp->next->value);
			else
				fd_list[i] = ft_redirect(tmp->next->value, tmp->type);
			if (fd_list[i] == -1)
				return (FALSE);
			i++;
		}
		tmp = tmp->next;
	}
	fd_list[i] = -1;
	return (TRUE);
}

int	**ft_redirect_init(t_token **token_list)
{
	int		**fd_list;
	int		i;
	int		check;
	t_token	*tokens;

	tokens = *token_list;
	fd_list = (int **)malloc(2 * sizeof(int *));
	if (fd_list == NULL)
		return (NULL);
	i = ft_redirections_count(tokens, INPUT, HEREDOC);
	fd_list[0] = (int *)malloc((i + 1) * sizeof(int));
	i = ft_redirections_count(tokens, TRUNC, APPEND);
	fd_list[1] = (int *)malloc((i + 1) * sizeof(int));
	if (fd_list[0] == NULL || fd_list[1] == NULL)
		return (NULL);
	check = ft_fd_list_check(tokens, INPUT, HEREDOC, fd_list[0]);
	if (check == TRUE)
		check = ft_fd_list_check(tokens, TRUNC, APPEND, fd_list[1]);
	if (check == FALSE)
	{
		ft_free_fd(fd_list);
		return (NULL);
	}
	return (fd_list);
}
