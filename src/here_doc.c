/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 16:19:30 by bpoetess          #+#    #+#             */
/*   Updated: 2022/08/29 16:59:22 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	here_doc_fd(char *stop_word)
{
	int		fds[2];
	char	tmp;

	if (!stop_word || pipe(fds) == -1)
		return (0);
	tmp = readline(YELLOW"> "RESETCOLOR);
	while (tmp && !ft_strncmp(tmp, stop_word, strlen(tmp) - 1)
		&& ft_strncmp(tmp, stop_word, strlen(tmp)) == '\n')
	{
		write(fds[1], tmp, ft_strlen(tmp));
		free (tmp);
		tmp = 0;
		tmp = readline(YELLOW"> "RESETCOLOR);
	}
	if (tmp)
		free (tmp);
	close (fds[1]);
	return (fds[0]);
}
