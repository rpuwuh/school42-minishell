/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sp_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 00:59:32 by dmillan           #+#    #+#             */
/*   Updated: 2022/10/09 01:18:56 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_free_line(char **s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return ;
	while (s[i] != NULL)
	{
		free(s[i]);
		i++;
	}
	free(s);
}

static void	ft_divide_words(char *s, char **words_new)
{
	int	i;
	int	j;
	int	count;

	i = -1;
	j = 0;
	count = 0;
	while (s[++i])
	{
		if (s[i] == '\'' || s[i] == '"')
			i = i + ft_create_word_sp_symb(s, words_new, i, j++);
		else if (s[i] == ' ' && (s[i - 1] && s[i - 1] != '|'))
		{
			words_new[j++] = ft_create_word(s, i - count, count);
			count = 0;
		}
		else if (s[i] == '|')
		{
			if ((s[i - 1] && s[i - 1] == ' ') && count)
				words_new[j++] = ft_create_word(s, i - count, count);
			words_new[j++] = ft_strdup("|");
			count = 0;
		}
		else if (s[i] != ' ')
			count++;
	}
	if (count)
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
