/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 20:58:12 by dmillan           #+#    #+#             */
/*   Updated: 2022/07/12 23:30:43 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

void	ft_exit_with_error(char *func, char *msg)
{
	write(STDERR_FILENO, RED, ft_strlen(RED));
	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, "Error", 5);
	if (func != NULL)
	{
		write(STDERR_FILENO, " in ", 4);
		write(STDERR_FILENO, func, ft_strlen(func));
		write(STDERR_FILENO, ": ", 2);
	}
	if (msg != NULL)
		write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, "\n", 1);
	write(STDERR_FILENO, RESETCOLOR, ft_strlen(RESETCOLOR));
	exit(EXIT_FAILURE);
}

int	ft_shell_init(t_env_v	**env, char **envp, char *prompt)
{
	char	*env_value;

	ft_env_init(env, envp);
	env_value = ft_env_get_value(*env, "SHLVL");
	if (env_value)
	{
		env_value = ft_itoa(ft_atoi(env_value) + 1);
		ft_env_replace(env, "SHLVL", env_value, 1);
		free(env_value);
	}
	env_value = getcwd(NULL, 1000);
	env_value = ft_strjoin(env_value, "/minishell");
	ft_env_replace(env, "SHELL", env_value, 1);
	free(env_value);
	prompt = ft_get_prompt(env);
	ft_env_add(env, ft_strdup("?"), ft_strdup("0"), FALSE);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	*prompt;
	t_env_v	**env;

	env = (t_env_v **)malloc(sizeof(t_env_v *));
	prompt = (char *)malloc(sizeof(char));
	if (argc > 1 && argv != NULL)
		ft_exit_with_error("minishell", INCORRECT_INPUT);
	if (signal(SIGINT, handle_signals) == SIG_ERR
		|| signal(SIGQUIT, handle_signals) == SIG_ERR)
		ft_exit_with_error("handle_signals", KERNEL_REG);
	if (ft_shell_init(env, envp, prompt))
		exit(EXIT_FAILURE);
	while (1)
	{
		line = readline(prompt);
		if (line != NULL)
			add_history(line);
		else
			ft_exit(NULL, CTRL_D, *env);
		ft_parser(line, env, envp);
	}
	exit(g_status);
}
