/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 20:58:12 by dmillan           #+#    #+#             */
/*   Updated: 2022/07/05 23:48:57 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error_and_exit(char *func, char *msg)
{
	ft_putstr_fd("Error in %s : %s.\n", func, msg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc > 1 && argv)
	{
		print_error_and_exit("minishell", INCORRECT_INPUT);
	}
	if (shell_init(envp))
		exit(EXIT_FAILURE);
	while (1)
	{
		if (shell_clear())
			break ;
		wait_input();
		if (g_shell.input_mode && main_inputmode())
			continue ;
		extract_paths();
		if (g_shell.original == NULL || !check_space(g_minishell.original))
			continue ;
		parse_input();
		execute_tokens();
		free_all();
	}
	return (0);
}
