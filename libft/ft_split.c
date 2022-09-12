/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 22:29:41 by dmillan           #+#    #+#             */
/*   Updated: 2022/09/12 01:59:52 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_line(char **s)
{
	int	i;

	if (s == NULL)
		return ;
	i = 0;
	while (s[i] != NULL)
	{
		free(s[i]);
		i++;
	}
	free(s);
}

static int	ft_wordnum(char const *s, char c)
{
	int	i;
	int	count;
	int	tmp;

	i = 0;
	count = 0;
	tmp = 0;
	while (s[i] != '\0')
	{
		if (s[i] < ' ' || s[i] > '~')
			return (0);
		else if (s[i] != c && tmp == 0)
		{
			count++;
			tmp = 1;
		}
		else if (s[i] == c)
			tmp = 0;
		i++;
	}
	return (count + 1);
}

static char	*ft_fillword(char const *s, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = (char *)malloc(sizeof(char) * (finish - start + 1));
	if (word == NULL)
		return (NULL);
	while (start < finish)
	{
		word[i] = s[start];
		i++;
		start++;
	}
	word[i] = '\0';
	return (word);
}

static void	ft_divide(char const *s, char c, char **words)
{
	size_t	i;
	int		j;
	int		start;

	i = 0;
	j = 0;
	start = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && start < 0)
			start = i;
		else if ((s[i] == c || i == ft_strlen(s)) && (start >= 0))
		{
			words[j] = ft_fillword(s, start, i);
			start = -1;
			j++;
		}
		words[j] = NULL;
		i++;
	}
}

char	**ft_split(char const *s, char c)
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
