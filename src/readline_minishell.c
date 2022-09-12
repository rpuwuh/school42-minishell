/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_minishell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 20:14:33 by bpoetess          #+#    #+#             */
/*   Updated: 2022/09/12 02:43:38 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*read_one_more_line(char *line, int cut_backslash)
{
	char	*tmp;

	if (cut_backslash)
	{
		tmp = ft_strndup(line, ft_strlen(line) - 1);
		free (line);
		line = tmp;
		tmp = readline("> ");
		if (!tmp)
			exit (0);
		line = ft_strjoin(line, tmp);
		free (tmp);
		return (line);
	}
	tmp = readline("> ");
	if (!tmp)
	{
		printf("minishell: synthax error: unexpected end of file\n");
		exit (258);
	}
	line = ft_strjoin(line, "\n");
	line = ft_strjoin(line, tmp);
	free (tmp);
	return (line);
}

static int	scroll_untill_double_quote(char *line, int *i, int *res)
{
	if (!line || !i)
		return (0);
	(*i)++;
	while (line[*i] && line[*i] != '\"')
	{
		if (line[*i] == '\\' && !line[*i + 1])
		{
			*res = 2;
			return (2);
		}
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
	res = 1;
	while (line && line[i])
	{
		while (line && line[i]
			&& line[i] != '\\' && line[i] != '\"' && line[i] != '\'')
			i++;
		if (line[i] == '\\' && !line[i + 1])
			return (2);
		else if (line[i] == '\\')
			i += 2;
		else if (line[i] == '\'' && scroll_untill_single_quote(line, &i))
			return (1);
		else if (line[i] == '\"' && scroll_untill_double_quote(line, &i, &res))
			return (res);
		else if (!line[i])
			return (0);
	}
	return (0);
}

char	*readline_minishell(char *prompt, t_env_v **env)
{
	char	*line;
	char	*tmp;

	line = readline_withoutspaces(prompt);
	if (!line)
		exit (0);
	while (check_for_addtional_readline(line))
	{
		if (check_for_addtional_readline(line) == 2)
			line = read_one_more_line(line, 1);
		else
			line = read_one_more_line(line, 0);
	}
	if (line && *line)
		add_history(line);
	else if (line)
		ft_exit(NULL, CTRL_D, *env);
	tmp = ft_strtrim(line, "\t\n\v\f\r ");
	free (line);
	line = tmp;
	return (line);
}
