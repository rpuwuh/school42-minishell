/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 00:59:32 by dmillan           #+#    #+#             */
/*   Updated: 2022/08/18 03:40:15 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_wordnum(char **s, char c)
{
	int	i;
	int	j;
	int	pipe_count;

	i = 0;
	pipe_count = 0;
	while (s[i])
	{
		j = 0;
		while (s[i][j])
		{
			if (s[i][j] == c)
			{
				if (s[i][j + 1] != ('\0' || ' '))
					pipe_count++;
				if (j != 0)
					pipe_count++;
			}
			j++;
		}
		i++;
	}
	printf("pipe_num = %d\n", pipe_count);
	printf("word_num = %d\n", i + pipe_count);
	return (i + pipe_count + 1);
}

static void	ft_divide(char **s, char c, char **words_new)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	while (s[i])
	{
		j = 0;
		while (s[i][j] && (s[i][j] != c || (j == 0 &&
				s[i][j] == c && s[i][j + 1] == (' ' || '\0'))))
			j++;
		if (j == (int)ft_strlen(s[i]))
			words_new[k] = ft_strdup(s[i]);
		else
		{
			if (j != 0)
			{
				printf("j = %d\n", j);
				words_new[k++] = ft_strdup(ft_substr(s[i], 0, (size_t)j));
			}
			words_new[k] = ft_strdup(&c);
			if (s[i][j + 1] && s[i][j + 1] != ' ')
				words_new[++k] = strdup(ft_substr(s[i],
							j + 1, ft_strlen(s[i])));
		}
		i++;
		k++;
	}
	words_new[k] = NULL;
}

char	**ft_sp_split(char **s, char c)
{
	char	**words;

	if (s == NULL)
		return (NULL);
	words = (char **)malloc(sizeof(char *) * ft_wordnum(s, c));
	if (!words)
		return (NULL);
	ft_divide(s, c, words);
	return (words);
}
