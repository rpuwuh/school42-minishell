/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 22:40:13 by dmillan           #+#    #+#             */
/*   Updated: 2022/07/09 23:51:20 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_redirections_exist(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp != NULL)
	{
		if (tmp->type != NONE)
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

int	ft_pipes_exist(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp != NULL)
	{
		if (tmp->type == PIPE)
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

void	ft_parse_redirections(t_env_v **env, t_token *tokens)
{
	int		pid;
	int		fd_in;
	int		fd_out;
	int		**arr;

	arr = create_array(tokens);
	if (arr == NULL)
		return ;
	fd_in = ft_get_fd(arr[0]);
	fd_out = ft_get_fd(arr[1]);
	pid = fork();
	if (pid == 0)
		ft_parse_red_child(tokens, fd_in, fd_out, env);
	else
	{
		close(fd_in);
		close(fd_out);
		wait (NULL);
	}
	free(arr[0]);
	free(arr[1]);
	free(arr);
	ft_remove_heredoc(env);
}

t_token	*ft_lexer(char **line)
{
	t_token	*tokens;

	if (line == NULL)
		return (NULL);
	tokens = ft_tokens_init();
	ft_tokens_get(tokens, line);
	ft_free_line(line);
	return (tokens);
}

void	ft_parser(char *line, t_env_v **env, char	**envp)
{
	t_token	*tokens;
	char	**input;

	//line = env_vars(line, env->env_v); //checks $$ at the end of the line (?)
	line = ft_remove_extra_spaces(line);
	tokens = ft_lexer(ft_split(line, ' '));
	if (line[0] != '\0' && ft_redirect_check(line) && ft_quotes_check(line))
	{
		ft_remove_quotes(tokens);
		if (ft_pipes_exist(tokens) == true)
			ft_parse_pipe(tokens, env, 0);
		else if (ft_redirections_exist(tokens) == true)
			ft_parse_redirections(env, tokens);
		else
		{
			input = ft_convert_tokens(tokens);
			if (input != NULL && input[0] != NULL)
				ft_executer(input, env, envp);
			if (input != NULL)
				ft_free_line(input);
		}
	}
	ft_free_tokens(tokens);
	free(line);
}
