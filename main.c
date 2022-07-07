/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 20:58:12 by dmillan           #+#    #+#             */
/*   Updated: 2022/07/08 00:01:29 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signals(int sig)
{
	if (sig == SIGINT)
	{
		g_status = 130;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	exit_with_error(char *func, char *msg)
{
	ft_putstr_fd("Error in %s: %s.\n", func, msg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	*prompt;
	t_env_v	**env;

	if (argc > 1 && argv != NULL)
		exit_with_error("minishell", INCORRECT_INPUT);
	if (signal(SIGINT, handle_signals) == SIG_ERR
		|| signal(SIGQUIT, handle_signals) == SIG_ERR)
		exit_with_error("handle_signals", KERNEL_REG);
	if (shell_init(env, envp, prompt))
		exit(EXIT_FAILURE);
	while (1)
	{
		line = readline(prompt);
		//else
			//line = readline(BLUE"minishell$ "RESETCOLOR);
		if (line != NULL)
			add_history(line);
		else
			ft_exit(NULL, CTRL_D, env);
		parser(line, env, envp);
	}
	exit(g_status);
}
