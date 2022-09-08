/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_minishell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 20:14:33 by bpoetess          #+#    #+#             */
/*   Updated: 2022/09/08 21:51:47 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	scroll_untill_double_quote(char *line, int *i)
{
	if (!line || !i)
		return (0);
	(*i)++;
	while (line[*i] && line[*i] != '\"')
	{
		if (line[*i] == '\\' && !line[*i + 1])
			return (1);
		else if (line[*i] == '\\')
			(*i)++;
		(*i)++;
	}
	if (!line[*i])
		return (1);
	if (line[*i] == '\"')
		(*i)++;
	return (0);
}

static int	scroll_untill_single_quote(char *line, int *i)
{
	if (!line || !i)
		return (0);
	(*i)++;
	while (line[*i] && line[*i] != '\'')
		(*i)++;
	if (!line[*i])
		return (1);
	if (line[*i] == '\'')
		(*i)++;
	return (0);
}

static int	check_for_addtional_readline(char *line)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (line && line[i])
	{
		while (line && line[i]
			&& line[i] != '\\' && line[i] != '\"' && line[i] != '\'')
			i++;
		if (line[i] == '\\' && !line[i + 1])
			res = 2;
		else if (line[i] == '\\')
			i += 2;
		else if (line[i] == '\'')
			res = scroll_untill_single_quote(line, &i);
		else if (line[i] == '\"')
			res = scroll_untill_double_quote(line, &i);
		else if (!line[i])
			return (res);
		i++;
	}
	return (res);
}

static char	*cut_backslash(char *line)
{
	char	*tmp;

	tmp = ft_strndup(line, ft_strlen(line) - 1);
	free (line);
	line = tmp;
	tmp = readline("> ");
	line = ft_strjoin(line, tmp);
	free (tmp);
	return (line);
}

char	*readline_minishell(char *prompt)
{
	char	*line;
	char	*tmp;

	line = readline(prompt);
	while (check_for_addtional_readline(line))
	{
		if (check_for_addtional_readline(line) == 2)
			line = cut_backslash(line);
		else
		{
			tmp = readline("> ");
			line = ft_strjoin(line, "\n");
			line = ft_strjoin(line, tmp);
			free (tmp);
		}
	}
	return (line);
}
