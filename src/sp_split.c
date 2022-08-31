/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sp_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 00:59:32 by dmillan           #+#    #+#             */
/*   Updated: 2022/09/01 00:47:55 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* static int	ft_wordnum(char **s, char c)
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
} */

static int	ft_sp_wordnum(char *s)
{
	int	i;
	int	j;
	int	quote_single;
	int	quote_double;

	i = 0;
	printf("check wordnum\n");
	quote_single = 0;
	quote_double = 0;
	while (s[i] == ' ' || s[i] == '|')
	{
		if (s[i] == '|')
			return (0);
		i++;
	}
	while (s[i])
	{
		if (s[i] == '\'')
		{
			if (quote_single == 0)
			{
				quote_single = 1;
				j++;
			}
			else if (quote_single == 1)
				quote_single = 0;
		}
		else if (s[i] == '"')
		{
			if (quote_double == 0)
			{
				quote_double = 1;
				j++;
				printf("quote detected\n");
			}
			else if (quote_double == 1)
				quote_double = 0;
		}
		else if (s[i] == ' ' && ((s[i + 1] && s[i + 1] != '|' && s[i + 1] != ' ')
			|| !s[i + 1]) && ((s[i - 1] && s[i - 1] != '|') || i == 0)
			&& quote_single == 0 && quote_double == 0)
			j++;
		else if (s[i] == ' ' && (s[i + 1] == ' ' || s[i + 1] == '|'))
			i++;
		else if (s[i] == '|' && quote_single == 0 && quote_double == 0)
		{
			j++;
			i++;
			if (s[i] && s[i] == ' ')
				i++;
		}
		i++;
	}

	i = 0;
	printf("word_num = %d\n", j);
	return (j);
}

char	*ft_create_word(char *s, unsigned int i, int len)
{
	char	*str;
	char	*tmp;

	tmp = ft_substr(s, i, len);
	str = ft_strdup(tmp);
	return (str);
}

static void	ft_sp_divide(char *s, char **words_new)
{
	int	i;
	int	j;
	int	k1;
	int	k2;
	int	count;
	int	quote_single;
	int	quote_double;

	i = 0;
	j = 0;
	k1 = 0;
	k2 = 0;
	count = 0;
	quote_single = 0;
	quote_double = 0;
	while (s[i] == ' ' || s[i] == '|')
	{
		if (s[i] == '|')
		{
			words_new = NULL;
			break ;
		}
		i++;
	}
	while (s[i])
	{
		if (s[i] == '\'')
		{
			if (quote_single == 0)
				quote_single = 1;
			else if (quote_single == 1)
			{
				quote_single = 0;
				words_new[j] = ft_create_word(s, i - k1, k1 + 1);
				j++;
				k1 = 0;
				i++;
			}
		}
		if (s[i] == '"')
		{
			if (quote_double == 0)
				quote_double = 1;
			else if (quote_double == 1)
			{
				quote_double = 0;
				words_new[j] = ft_create_word(s, i - k2, k2 + 1);
				j++;
				k2 = 0;
				i++;
			}
		}
		if (quote_single == 1)
			k1++;
		if (quote_double == 1)
			k2++;
		if (s[i] == ' ' && (i == 0 || (s[i - 1] && s[i - 1] != ('|' || ' ')))
			&& quote_single == 0 && quote_double == 0)
		{
			words_new[j] = ft_create_word(s, i - count, count);
			j++;
			count = 0;
		}
		if (s[i] == '|' && quote_single == 0 && quote_double == 0)
		{
			if (i == 0 || (s[i - 1] && s[i - 1] == ' '))
			{
				words_new[j] = ft_strdup("|");
				j++;
				count = 0;
			}
			else
			{
				words_new[j] = ft_create_word(s, i - count, count);
				j++;
				words_new[j] = ft_strdup("|");
				j++;
				count = 0;
			}
		}
		if (k1 == 0 && k2 == 0 && s[i] != ' ')
			count++;
		i++;
		if (j >= 1)
			printf ("word is = %s\n", words_new[j - 1]);
	}
	words_new[j] = NULL;
}

char	**sp_split(char *str)
{
	char	**words;

	if (str == NULL)
		return (NULL);
	printf("check 0\n");
	words = (char **)malloc(sizeof(char *) * ft_sp_wordnum(str));
	if (words == NULL)
		return (NULL);
	ft_sp_divide(str, words);

	int i = 0;
	printf("word = ");
	while (words[i])
		printf("%s ", words[i++]);

	return (words);
}
