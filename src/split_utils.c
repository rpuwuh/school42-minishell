/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 02:27:54 by dmillan           #+#    #+#             */
/*   Updated: 2022/10/17 23:32:08 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_count_quotes(char *s, int i)
{
	int	sp_c;
	int	len;

	sp_c = s[i];
	len = 1;
	while (s[++i] != sp_c)
		len++;
	return (len);
}

int	ft_sp_wordnum(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			count++;
			i = i + ft_count_quotes(s, i);
		}
		else if ((s[i] == ' ' && (s[i - 1] != '|')) || s[i + 1] == '\0')
			count++;
		else if (s[i] == '|')
		{
			if (i == 0 || s[i - 1] != ' ')
				count++;
			count++;
		}
		i++;
	}
	count++;
	return (count);
}

char	*ft_create_word(char *s, unsigned int i, int len)
{
	char	*str;
	char	*tmp;

	if (s[i + len + 1] == '\0')
		len++;
	printf ("i = %u\n", i);
	printf ("len = %d\n", len);
	tmp = ft_substr(s, i, len);
	str = ft_strdup(tmp);
	free (tmp);
	printf ("str = %s\n", str);
	return (str);
}

int	ft_create_word_sp_symb(char *s, char **words_new,
			unsigned int i, unsigned int j)
{
	int		len;
	char	*tmp;
	char	sp_c;
	int		start;

	sp_c = s[i];
	len = 1;
	start = i;
	while (s[++i] != sp_c)
		len++;
	len++;
	printf("len = %d\n", len);
	tmp = ft_substr(s, start, len);
	printf ("tmp = %s\n", tmp);
	words_new[j] = ft_strdup(tmp);
	free (tmp);
	return (len);
}
