/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_remove.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 23:53:24 by dmillan           #+#    #+#             */
/*   Updated: 2022/07/15 02:28:11 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_insert_env(t_token *tmp, t_env_v **env, int i)
{
	int		j;
	int		k;
	int		l;
	int		n_size;
	char	*value;
	char	*env_value;

	n_size = 0;
	while (tmp->value[i + n_size] != ' ' && tmp->value[i + n_size] != '\0')
		n_size++;
	env_value = ft_env_get_value(*env, ft_strndup(ft_substr(tmp->value, i, (size_t)n_size), n_size));
	value = malloc((ft_strlen(tmp->value) - n_size + ft_strlen(env_value) + 1) * sizeof(char));
	j = -1;
	while (++j < i - 1)
		value[j] = tmp->value[j];
	k = -1;
	while (++k < (int)ft_strlen(env_value))
		value[j + k] = env_value[k];
	l = -1;
	while (tmp->value[++l + j + 1 + n_size] != '\0')
		value[j + k + l] = tmp->value[j + 1 + n_size + l];
	value[j + k + l] = '\0';
	return (value);
}

char	*ft_check_for_env(t_token *tmp, t_env_v **env)
{
	int	i;

	i = 0;
	while (tmp->value[i] != '\0')
	{
		if (tmp->value[i] == '$')
		{
			tmp->value = ft_insert_env(tmp, env, i + 1);
			break ;
		}
		i++;
	}
	return (tmp->value);
}

static int	ft_get_quoted_size(char *s, char c)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (s[i] != '\0')
	{
		if (c == ' ' && (s[i] == '\'' || s[i] == '"'))
			c = s[i];
		else if (s[i] == c)
			c = ' ';
		else
			size++;
		i++;
	}
	return (size);
}

static char	*ft_quotes_replace(t_token *tmp, char c)
{
	int		i;
	int		j;
	char	*quoted;

	i = ft_get_quoted_size(tmp->value, c);
	quoted = (char *)malloc((i + 1) * sizeof(char));
	if (quoted == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (tmp->value[i] != '\0')
	{
		if (c == ' ' && (tmp->value[i] == '\'' || tmp->value[i] == '"'))
			c = tmp->value[i];
		else if (tmp->value[i] == c)
			c = ' ';
		else
		{
			quoted[j] = tmp->value[i];
			j++;
		}
		i++;
	}
	quoted[j] = '\0';
	return (quoted);
}

void	ft_quotes_remove(t_token *tokens, t_env_v **env)
{
	t_token	*tmp;
	char	symb;
	int		i;

	tmp = tokens;
	i = 0;
	while (tmp != NULL)
	{
		symb = tmp->value[0];
		if (symb == '\'' && ft_strlen(tmp->value) >= 2)
			tmp->value = ft_quotes_replace(tmp, ' ');
		if (symb == '"' && ft_strlen(tmp->value) >= 2)
		{
			tmp->value = ft_quotes_replace(tmp, ' ');
			tmp->value = ft_check_for_env(tmp, env);
		}
		tmp = tmp->next;
		i = 0;
	}
}
