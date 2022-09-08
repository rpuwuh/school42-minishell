/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_withoutspaces.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 00:02:22 by bpoetess          #+#    #+#             */
/*   Updated: 2022/09/09 00:08:50 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	readline_withoutspaces_check_emptiness(char *line)
{
	char	*tmp;

	tmp = ft_strtrim(line, "\t\n\v\f\r ");
	if (!tmp)
		return (1);
	if (!tmp[0])
	{
		free (tmp);
		return (1);
	}
	free (tmp);
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
