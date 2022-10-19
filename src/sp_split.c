/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sp_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 00:59:32 by dmillan           #+#    #+#             */
/*   Updated: 2022/10/19 22:38:43 by dmillan          ###   ########.fr       */
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

static void	ft_divide_words(char *s, char **words_new, int count)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (s[++i])
	{
		if (s[i] == '\'' || s[i] == '"')
			i = i + ft_create_word_sp_symb(s, words_new, i, j++);
		else if ((s[i] == ' ' && (s[i - 1] != '|')) || s[i + 1] == '\0')
		{
			words_new[j++] = ft_create_word(s, i - count, count);
			count = 0;
		}
		else if (s[i] == '|')
		{
			if (count)
				words_new[j++] = ft_create_word(s, i - count, count);
			words_new[j++] = ft_strdup("|");
			count = 0;
		}
		else if (s[i] != ' ')
			count++;
	}
	words_new[j] = NULL;
}

char	**ft_sp_split(char *str)
{
	char	**words;
	int		count;

	if (str == NULL)
		return (NULL);
	words = (char **)malloc(sizeof(char *) * ft_sp_wordnum(str));
	if (words == NULL)
		return (NULL);
	count = 0;
	ft_divide_words(str, words, count);
	return (words);
}
