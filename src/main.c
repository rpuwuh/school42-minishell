/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 20:58:12 by dmillan           #+#    #+#             */
/*   Updated: 2022/10/05 07:37:27 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_status;

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

int	ft_shell_init(t_env_v **env, char **envp)
{
	char	*env_value;

	ft_env_init(env, envp);
	env_value = ft_env_get_value(*env, "SHLVL");
	if (env_value)
	{
		env_value = ft_itoa(ft_atoi(env_value) + 1);
		ft_env_replace(env, "SHLVL", env_value, 1);
	}
	env_value = getcwd(NULL, 1000);
	env_value = ft_strjoin(env_value, "/minishell");
	ft_env_replace(env, "SHELL", env_value, 1);
	ft_env_add(env, ft_strdup("?"), ft_strdup("0"), FALSE);
	printf("\nSHLVL_value = %s\n", ft_env_get_value(*env, "SHLVL"));
	printf("SHELL_value = %s\n", ft_env_get_value(*env, "SHELL"));
	return (0);
}

void	ft_line_handler(t_env_v **env, char *line, t_cmd_list	*cmd_list)
{
	char	*prompt;

	ft_tty_mask();
	prompt = ft_get_prompt(env);
	ft_signals_run(1);
	line = readline_minishell(prompt, env);
	line = stringnormalizespaces(line);
	printf("\tline = <%s>\n", line); // delete this line before release
	ft_parser(line, env, ft_cmd_init(cmd_list, env));
	ft_cmd_free(cmd_list);
	printf("cmd_cleaned\n");
	free(line);
	line = 0;
	free(prompt);
	prompt = 0;
	ft_signals_run(1);
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_env_v		**env;
	t_cmd_list	*cmd_list;

	env = (t_env_v **)malloc(sizeof(t_env_v *));
	cmd_list = (t_cmd_list *)malloc(sizeof(t_cmd_list));
	line = (char *)malloc(sizeof(char));
	if (argc > 1 && argv != NULL)
		ft_exit_with_error("minishell", INCORRECT_INPUT);
	if (ft_shell_init(env, envp))
		exit(EXIT_FAILURE);
	while (1)
		ft_line_handler(env, line, cmd_list);
	exit(g_status);
}
