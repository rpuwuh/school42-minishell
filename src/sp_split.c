/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sp_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 00:59:32 by dmillan           #+#    #+#             */
/*   Updated: 2022/09/27 02:57:30 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_divide_words(char *s, char **words_new)
{
	int	i;
	int	j;
	int	count;

	i = -1;
	j = 0;
	while (s[++i])
	{
		if (s[i] == '\'' || s[i] == '"')
			i = i + ft_create_word_sp_symb(s, words_new, i, j++);
		else if (s[i] == ' ' && (s[i - 1] && s[i - 1] != ('|' || ' ')))
		{
			words_new[j++] = ft_create_word(s, i - count, count);
			count = 0;
		}
		else if (s[i] == '|')
		{
			j = j + ft_create_pipe_symb(s, words_new, i++, j, count);
			count = 0;
		}
		else if (s[i] != ' ')
			count++;
	}
	words_new[j++] = ft_create_word(s, i - count, count);
	words_new[j] = NULL;
}

char	**sp_split(char *str)
{
	char	**words;

	if (str == NULL)
		return (NULL);
	words = (char **)malloc(sizeof(char *) * ft_sp_wordnum(str));
	if (words == NULL)
		return (NULL);
	ft_divide_words(str, words);
	return (words);
}
