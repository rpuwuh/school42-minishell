/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_convert.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 23:04:39 by dmillan           #+#    #+#             */
/*   Updated: 2022/10/19 21:21:54 by bpoetess         ###   ########.fr       */
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
	int		size;
	t_token	*tmp;

	size = 0;
	tmp = token;
	while (tmp)
	{
		tmp = tmp->next;
		size++;
	}
	ft_tokens_free(tmp);
	return (size);
}

t_token	*ft_tokens_invert(t_token *tokens)
{
	t_token	*token_inv;
	t_token	*tmp_prev;
	t_token	*tmp;

	tmp = tokens;
	token_inv = NULL;
	while (tmp)
	{
		ft_token_add(&token_inv, tmp);
		tmp_prev = tmp;
		tmp = tmp->next;
		if (tmp_prev)
			free (tmp_prev);
	}
	tokens = token_inv;
	return (tokens);
}

char	**ft_tokens_convert(t_token *tokens)
{
	char	**command;
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = tokens;
	i = ft_token_size(tmp);
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
	ft_tokens_free(tokens);
	return (command);
}

char	**ft_tokens_convert_redirect(t_token *tokens)
{
	char	**command;
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = tokens;
	i = ft_token_size(tmp);
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
	ft_tokens_free(tokens);
	return (command);
}
