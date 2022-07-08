/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 22:56:08 by dmillan           #+#    #+#             */
/*   Updated: 2022/07/09 00:36:45 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_quotes_correct(char *s, int pos, char quote, char other)
{
	int	count;
	int	count_other;
	int	i;

	if (quote == '"' && ft_quotes_correct(s, pos, '\'', '"') == 1)
		return (true);
	count = 0;
	count_other = 0;
	i = 0;
	while (i < pos)
	{
		if (s[i] == other && count % 2 == 0)
			count_other++;
		else if (s[i] == quote && count_other % 2 == 0)
			count++;
		i++;
	}
	if (count % 2 == 0)
		return (false);
	return (true);
}

int	check_quotes(char *s)
{
	if (ft_quotes_correct(s, ft_strlen(s), '"', '\'') == FALSE)
		return (TRUE);
	ft_exit_with_error("quotes", "not balanced out");
	return (FALSE);
}

static int	check_space(char *s, int i)
{
	if (s[i] != ' ' || (i > 0 && s[i] == ' ' && s[i - 1] != ' '))
		return (FALSE);
	else if ((s[i] == ' '
		&& ft_quotes_correct(s, i, '"', '\'') == TRUE))
		return (FALSE);
	return (TRUE);
}

char	*remove_extra_spaces(char *s)
{
	int		i;
	int		size;
	char	*word;

	i = 0;
	size = 0;
	while (s[i] != '\0')
	{
		if (check_space(s, i) == FALSE)
			size++;
		i++;
	}
	ret = malloc(size + 1);
	ret[size] = '\0';
	while (i >= 0)
	{
		if (check_space(s, i) == FALSE)
		{
			ret[size] = s[i];
			size--;
		}
		i--;
	}
	free(s);
	return (ret);
}