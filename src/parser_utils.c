/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 22:56:08 by dmillan           #+#    #+#             */
/*   Updated: 2022/07/09 23:50:19 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_get_fd(int	*fd_list)
{
	int	i;

	i = 0;
	while (fd_list[i] != -1)
	{
		if (fd_list[i + 1] == -1)
			return (fd_list[i]);
		close(fd_list[i]);
		i++;
	}
	return (-1);
}

int	ft_quotes_correct(char *s, int pos, char symb1, char symb2)
{
	int	count_symb1;
	int	count_symb2;
	int	i;

	if (symb1 == '"' && ft_quotes_correct(s, pos, '\'', '"') == 1)
		return (TRUE);
	count_symb1 = 0;
	count_symb2 = 0;
	i = 0;
	while (i < pos)
	{
		if (s[i] == symb2 && count_symb1 % 2 == 0)
			count_symb2++;
		else if (s[i] == symb1 && count_symb2 % 2 == 0)
			count_symb1++;
		i++;
	}
	if (count_symb1 % 2 == 0)
		return (FALSE);
	return (TRUE);
}

static int	ft_quotes_check(char *s)
{
	if (ft_quotes_correct(s, ft_strlen(s), '"', '\'') == FALSE)
		return (TRUE);
	ft_exit_with_error("quotes", "not balanced out");
	return (FALSE);
}

static int	ft_check_space(char *s, int i)
{
	if (s[i] != ' ' || (i > 0 && s[i] == ' ' && s[i - 1] != ' '))
		return (FALSE);
	else if ((s[i] == ' '
			&& ft_quotes_correct(s, i, '"', '\'') == TRUE))
		return (FALSE);
	return (TRUE);
}

char	*ft_remove_extra_spaces(char *s)
{
	int		i;
	int		size;
	char	*word;

	i = 0;
	size = 0;
	while (s[i] != '\0')
	{
		if (ft_check_space(s, i) == FALSE)
			size++;
		i++;
	}
	word = malloc(size + 1);
	word[size] = '\0';
	while (i >= 0)
	{
		if (ft_check_space(s, i) == FALSE)
		{
			word[size] = s[i];
			size--;
		}
		i--;
	}
	free(s);
	return (ret);
}