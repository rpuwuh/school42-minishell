/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 23:08:46 by dmillan           #+#    #+#             */
/*   Updated: 2022/07/08 00:03:51 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(char **args, int ctrl_d, t_env_v *env_v)
{
	if (ctrl_d == TRUE)
	{
		rl_replace_line("", 0);
		printf("\33[1A");
		rl_on_new_line();
		rl_redisplay();
	}
	write(1, "exit\n", 5);
	rl_clear_history();
	if (args != NULL && args[1] != NULL)
	{
		if (ft_isnum(args[1]) == FALSE)
			exit_with_error("exit", args[1], "numeric argument required");
		else if (args[2] != NULL)
		{
			exit_with_error(NULL, "exit", "too many arguments");
			return ;
		}
		exit(free_arg(args, env_v));
	}
	exit(free_arg(args, env_v));
}
