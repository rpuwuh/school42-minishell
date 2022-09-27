/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 02:27:54 by dmillan           #+#    #+#             */
/*   Updated: 2022/09/27 02:54:11 by dmillan          ###   ########.fr       */
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
	count = 1;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			count++;
			i = i + ft_count_quotes(s, i);
		}
		else if (s[i] == ' ' && (s[i - 1] && s[i - 1] != ('|' || ' ')))
			count++;
		else if (s[i] == '|')
		{
			if (i == 0 || (s[i - 1] && s[i - 1] == ' '))
				count++;
			else
				count = count + 2;
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

	sp_c = s[i];
	len = 1;
	while (s[++i] != sp_c)
		len++;
	printf("len = %d\n", len);
	tmp = ft_substr(s, i, len);
	printf ("tmp = %s\n", tmp);
	words_new[j] = ft_strdup(tmp);
	free (tmp);
	return (len);
}

int	ft_create_pipe_symb(char *s, char **words_new, unsigned int i,
				unsigned int j, unsigned int count)
{
	if (i == 0 || (s[i - 1] && s[i - 1] == ' '))
	{
		words_new[j++] = ft_strdup("|");
		return (1);
	}
	else
	{
		words_new[j++] = ft_create_word(s, i - count, count);
		words_new[j++] = ft_strdup("|");
		return (2);
	}
}
