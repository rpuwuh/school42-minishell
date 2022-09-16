/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 16:19:30 by bpoetess          #+#    #+#             */
/*   Updated: 2022/09/16 16:39:54 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	stop_prompt(int sig)
{
	g_status = 130;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	// rl_on_new_line();
	// rl_redisplay();
	(void)sig;
}

int	here_doc_fd(char *stop_word)
{
	int		fds[2];
	char	*tmp;

	if (!stop_word || !*stop_word || pipe(fds) < 0)
		return (-1);
	ft_signals_run(3);
	signal(SIGINT, stop_prompt);
	tmp = readline(YELLOW"> "RESETCOLOR);
	while (g_status != 130 && ((tmp && !*tmp)
			|| (tmp && ft_strncmp(tmp, stop_word, strlen(tmp)))))
	{
		write(fds[1], "\n", 1);
		write(fds[1], tmp, ft_strlen(tmp));
		free (tmp);
		tmp = 0;
		tmp = readline(YELLOW"> "RESETCOLOR);
	}
	if (tmp)
		free (tmp);
	if (g_status != 130)
		write(fds[1], "\n", 1);
	else
		g_status = 0;
	close (fds[1]);
	return (fds[0]);
}

/*
while ((g_status != 130) && (tmp
			&& ft_strncmp(tmp, stop_word, strlen(tmp))))
	{
		ft_signals_run(4);
		write(fds[1], "\n", 1);
		write(fds[1], tmp, ft_strlen(tmp));
		free (tmp);
		tmp = 0;
		tmp = readline(YELLOW"> "RESETCOLOR);
	}
	if (tmp)
		free (tmp);
	if (g_status != 130)
		write(fds[1], "\n", 1);
	else
		g_status = 0;
	close (fds[1]);
	return (fds[0]);
*/