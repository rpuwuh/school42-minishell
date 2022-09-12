/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stringnormalizespaces.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 22:58:02 by bpoetess          #+#    #+#             */
/*   Updated: 2022/09/12 03:30:34 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	scroll_untill_double_quote(char *line, int *i)
{
	if (!line || !i)
		return ;
	(*i)++;
	while (line[*i] && line[*i] != '\"')
	{
		if (line[*i] == '\\')
			(*i)++;
		(*i)++;
	}
	if (line[*i] == '\"')
		(*i)++;
	return ;
}

static void	scroll_untill_single_quote(char *line, int *i)
{
	if (!line || !i)
		return ;
	(*i)++;
	while (line[*i] && line[*i] != '\'')
		(*i)++;
	if (line[*i] == '\'')
		(*i)++;
	return ;
}

static char	*copy_until_space_charecter(char *line, int *i)
{
	char	*res;

	*i = 0;
	while (line && line[*i] && !ft_isspace(line[*i]))
	{
		while (line && line[*i] && !ft_isspace(line[*i])
			&& line[*i] != '\\' && line[*i] != '\"' && line[*i] != '\'')
			(*i)++;
		if (line[*i] == '\\')
			(*i) += 2;
		else if (line[*i] == '\'')
			scroll_untill_single_quote(line, i);
		else if (line[*i] == '\"')
			scroll_untill_double_quote(line, i);
	}
	res = ft_strndup(line, *i);
	return (res);
}

static char	*copy_until_non_space_charecter(char *res, char *line, int *i)
{
	char	*tmp;
	int		j;

	while (line && line[*i] && ft_isspace(line[*i]))
		(*i)++;
	res = ft_strjoin(res, " ");
	tmp = ft_strdup(line + (*i));
	j = 0;
	while (tmp && tmp[j])
	{
		while (tmp && tmp[j] && !ft_isspace(tmp[j])
			&& tmp[j] != '\\' && tmp[j] != '\"' && tmp[j] != '\'')
			j++;
		if (tmp[j] == '\\')
			j += 2;
		else if (tmp[j] == '\'')
			scroll_untill_single_quote(tmp, &j);
		else if (tmp[j] == '\"')
			scroll_untill_double_quote(tmp, &j);
		else if (tmp[j] && ft_isspace(tmp[j]))
			tmp[j] = '\0';
	}
	res = ft_strjoin(res, tmp);
	free (tmp);
	return (res);
}

char	*stringnormalizespaces(char *line)
{
	char	*res;
	int		i;

	printf("\t\tim here!\n");
	res = copy_until_space_charecter(line, &i);
	while (line && line[i])
	{
		while (line && line[i] && !ft_isspace(line[i])
			&& line[i] != '\\' && line[i] != '\"' && line[i] != '\'')
			i++;
		if (line[i] == '\\')
			i += 2;
		else if (line[i] == '\'')
			scroll_untill_single_quote(line, &i);
		else if (line[i] == '\"')
			scroll_untill_double_quote(line, &i);
		else if (line[i] && ft_isspace(line[i]))
			res = copy_until_non_space_charecter(res, line, &i);
	}
	free (line);
	line = ft_strdup(res);
	free (res);
	return (line);
}
