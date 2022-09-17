/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 16:19:30 by bpoetess          #+#    #+#             */
/*   Updated: 2022/09/17 17:06:17 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	event(void)
{
	return (0);
}

static void	stop_prompt(int sig)
{
	g_status = 130;
	rl_done = 1;
	rl_replace_line("", 0);
	rl_redisplay();
	(void)sig;
}

static int	here_doc_loop(char *stop_word, int fd)
{
	char	*tmp;
	int		first_line;

	first_line = 1;
	rl_event_hook = event;
	tmp = readline(YELLOW"> "RESETCOLOR);
	while (g_status != 130 && ((tmp && !*tmp)
			|| (tmp && ft_strncmp(tmp, stop_word, strlen(tmp)))))
	{
		if (!first_line)
			write(fd, "\n", 1);
		write(fd, tmp, ft_strlen(tmp));
		free (tmp);
		first_line = 0;
		tmp = 0;
		tmp = readline(YELLOW"> "RESETCOLOR);
	}
	if (tmp)
		free (tmp);
	if (g_status == 130)
		return (-1);
	return (0);
}

int	here_doc_fd(char *stop_word)
{
	int		fds[2];
	int		res;

	if (!stop_word || !*stop_word || pipe(fds) < 0)
		return (-1);
	ft_signals_run(3);
	signal(SIGINT, stop_prompt);
	res = here_doc_loop(stop_word, fds[1]);
	close (fds[1]);
	rl_done = 0;
	g_status = 0;
	if (res == -1)
	{
		close (fds[0]);
		return (-1);
	}
	return (fds[0]);
}
