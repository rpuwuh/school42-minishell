/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_remove.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 23:53:24 by dmillan           #+#    #+#             */
/*   Updated: 2022/07/11 00:16:49 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_get_quoted_size(char *s, char c)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (s[i] != '\0')
	{
		if (c == ' ' && (s[i] == '\'' || s[i] == '"'))
			c = s[i];
		else if (s[i] == c)
			c = ' ';
		else
			size++;
		i++;
	}
	return (size);
}

static char	*ft_quotes_replace(t_token *tmp, char c)
{
	int		i;
	int		j;
	char	*quoted;

	i = ft_get_quoted_size(tmp->value, c);
	quoted = (char *)malloc((i + 1) * sizeof(char));
	if (quoted == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (tmp->value[i] != '\0')
	{
		if (c == ' ' && (tmp->value[i] == '\'' || tmp->value[i] == '"'))
			c = tmp->value[i];
		else if (tmp->value[i] == c)
			c = ' ';
		else
		{
			quoted[j] = tmp->value[i];
			j++;
		}
		i++;
	}
	quoted[j] = '\0';
	return (quoted);
}

void	ft_quotes_remove(t_token *tokens)
{
	t_token	*tmp;
	char	symb;

	tmp = tokens;
	while (tmp != NULL)
	{
		symb = tmp->value[0];
		if ((symb == '\'' || symb == '"') && ft_strlen(tmp->value) >= 2)
		{
			tmp->value = replace_quotes(tmp, ' ');
			if (symb == '\'')
				tmp->quotes = SINGLE;
			else if (symb == '"')
				tmp->quotes = DOUBLE;
		}
		tmp = tmp->next;
	}
}
