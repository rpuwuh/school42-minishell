/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_convert.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 23:04:39 by dmillan           #+#    #+#             */
/*   Updated: 2022/08/08 23:49:00 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	**ft_tokens_invert(t_token **tokens)
{
	t_token	**token_inv_list;
	t_token	*token_inv;
	t_token	*tmp;

	tmp = *tokens;
	token_inv = NULL;
	while (tmp)
	{
		ft_token_add(&token_inv, tmp);
		tmp = tmp->next;
	}
	token_inv_list = &token_inv;
	return (token_inv_list);
}

char	**ft_tokens_convert(t_token **tokens)
{
	char	**command;
	t_token	*tmp;
	t_token	*tmp2;
	int		i;

	i = 0;
	tmp = *tokens;
	tmp2 = *tokens;
	while (tmp2)
	{
		tmp2 = tmp2->next;
		i++;
	}
	command = (char **)malloc((i + 1) * sizeof(char *));
	if (command == NULL)
		return (NULL);
	tmp = *tokens;
	i = 0;
	while (tmp != NULL)
	{
		command[i] = ft_strdup(tmp->value);
		tmp = tmp->next;
		i++;
	}
	command[i] = NULL;
	return (command);
}
