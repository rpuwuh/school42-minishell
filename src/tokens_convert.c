/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_convert.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 23:04:39 by dmillan           #+#    #+#             */
/*   Updated: 2022/10/19 19:45:32 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_free_fd(int	**fd_list)
{
	free(fd_list[0]);
	free(fd_list[1]);
	free(fd_list);
}

int	ft_token_size(t_token *token)
{
	int	size;

	size = 0;
	while (token)
	{
		token = token->next;
		size++;
	}
	return (size);
}

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
	i = ft_token_size(tmp2);
	command = (char **)malloc((i + 1) * sizeof(char *));
	if (command == NULL)
		return (NULL);
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

char	**ft_tokens_convert_redirect(t_token **tokens)
{
	char	**command;
	t_token	*tmp;
	t_token	*tmp2;
	int		i;

	i = 0;
	tmp = *tokens;
	tmp2 = *tokens;
	i = ft_token_size(tmp2);
	command = (char **)malloc((i + 1) * sizeof(char *));
	if (command == NULL)
		return (NULL);
	i = 0;
	while (tmp != NULL)
	{
		if (tmp->type != NONE)
			tmp = tmp->next->next;
		else
		{
			command[i++] = ft_strdup(tmp->value);
			tmp = tmp->next;
		}
	}
	command[i] = NULL;
	return (command);
}
