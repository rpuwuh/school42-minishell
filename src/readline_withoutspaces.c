/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_withoutspaces.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 00:02:22 by bpoetess          #+#    #+#             */
/*   Updated: 2022/09/11 23:06:11 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_isspace(int c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ')
		return ((int) c);
	return ((int) 0);
}

static int	readline_withoutspaces_check_emptiness(char *line)
{
	int	i;

	if (!line)
		return (1);
	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (!line[0])
		return (1);
	return (0);
}

char	*readline_withoutspaces(char *prompt)
{
	char	*line;

	line = readline(prompt);
	while (line && readline_withoutspaces_check_emptiness(line))
	{
		free (line);
		line = readline(prompt);
	}
	if (!line)
	{
		printf("exit\n");
		exit(0);
	}
	return (line);
}
