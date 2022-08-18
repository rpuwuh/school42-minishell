/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 23:10:17 by dmillan           #+#    #+#             */
/*   Updated: 2022/08/18 23:17:55 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_prompt_restore(int sig)
{
	g_status = 130;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void)sig;
}

void	ft_ctrl_c(int sig)
{
	g_status = 130;
	write(1, "\n", 1);
	(void)sig;
}

void	ft_backslash(int sig)
{
	g_status = 131;
	printf("Quit (core dumped)\n");
	(void)sig;
}

void	ft_signals_run(int sig)
{
	if (sig == 1)
	{
		signal(SIGINT, ft_prompt_restore);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sig == 2)
	{
		signal(SIGINT, ft_ctrl_c);
		signal(SIGQUIT, ft_backslash);
	}
}
