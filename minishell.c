/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 22:45:04 by bpoetess          #+#    #+#             */
/*   Updated: 2022/07/07 06:27:30 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*s;

	(void) argc;
	(void) env;
	(void) argv;
	s = getcwd(0, 0);
	printf("%s\n", s);
	free(s);
	s = readline("minishell>");
	// rl_replace_line();
	printf("%s", s);
	free (s);
}
