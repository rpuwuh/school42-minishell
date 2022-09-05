/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sp_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 00:59:32 by dmillan           #+#    #+#             */
/*   Updated: 2022/09/05 23:25:03 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_sp_wordnum(char *s)
{
	int	i;
	int	j;
	int	quote_counter[2];

	i = 0;
	j = 1;
	quote_counter[0] = 0;
	quote_counter[1] = 0;
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
			if (quote_counter[0] == 0)
			{
				quote_counter[0] = 1;
				j++;
			}
			else if (quote_counter[0] == 1)
				quote_counter[0] = 0;
		}
		else if (s[i] == '"')
		{
			if (quote_counter[1] == 0)
			{
				quote_counter[1] = 1;
				j++;
			}
			else if (quote_counter[1] == 1)
				quote_counter[1] = 0;
		}
		else if (s[i] == ' ' && ((s[i + 1] && s[i + 1] != '|' && s[i + 1]
					!= ' ') || !s[i + 1]) && ((s[i - 1] && s[i - 1] != '|')
				|| i == 0) && quote_counter[0] == 0 && quote_counter[1] == 0)
			j++;
		else if (s[i] == ' ' && (s[i + 1] == ' ' || s[i + 1] == '|'))
			i++;
		else if (s[i] == '|' && quote_counter[0] == 0 && quote_counter[1] == 0)
		{
			j++;
			i++;
			if (s[i] && s[i] == ' ')
				i++;
		}
		i++;
	}
	return (j);
}

char	*ft_create_word(char *s, unsigned int i, int len)
{
	char	*str;
	char	*tmp;

	tmp = ft_substr(s, i, len);
	str = ft_strdup(tmp);
	free (tmp);
	return (str);
}

static void	ft_sp_divide(char *s, char **words_new)
{
	int	i;
	int	j;
	int	count[3];
	int	quote_counter[2];

	i = 0;
	j = 0;
	while (i < 3)
		count[i++] = 0;
	quote_counter[0] = 0;
	quote_counter[1] = 0;
	i = 0;
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
			if (quote_counter[0] == 0)
				quote_counter[0] = 1;
			else if (quote_counter[0] == 1)
			{
				quote_counter[0] = 0;
				words_new[j++] = ft_create_word(s, i - count[1], count[1] + 1);
				count[1] = 0;
				i++;
			}
		}
		if (s[i] == '"')
		{
			if (quote_counter[1] == 0)
				quote_counter[1] = 1;
			else if (quote_counter[1] == 1)
			{
				quote_counter[1] = 0;
				words_new[j++] = ft_create_word(s, i - count[2], count[2] + 1);
				count[2] = 0;
				i++;
			}
		}
		if (quote_counter[0] == 1)
			count[1]++;
		if (quote_counter[1] == 1)
			count[2]++;
		if (s[i] == ' ' && (i == 0 || (s[i - 1] && s[i - 1] != ('|' || ' ')))
			&& quote_counter[0] == 0 && quote_counter[1] == 0)
		{
			words_new[j++] = ft_create_word(s, i - count[0], count[0]);
			count[0] = 0;
		}
		if (s[i] == '|' && quote_counter[0] == 0 && quote_counter[1] == 0)
		{
			if (i == 0 || (s[i - 1] && s[i - 1] == ' '))
			{
				words_new[j++] = ft_strdup("|");
				i++;
				count[0] = 0;
			}
			else
			{
				words_new[j++] = ft_create_word(s, i - count[0], count[0]);
				i++;
				words_new[j++] = ft_strdup("|");
				count[0] = 0;
			}
		}
		if (count[1] == 0 && count[2] == 0 && s[i] != ' ')
			count[0]++;
		i++;
	}
	words_new[j++] = ft_create_word(s, i - count[0], count[0]);
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
	ft_sp_divide(str, words);

	int i = 0;
	printf("word = ");
	while (words[i])
		printf("%s ", words[i++]);
	printf("\n");

	return (words);
}
