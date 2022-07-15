/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 22:40:13 by dmillan           #+#    #+#             */
/*   Updated: 2022/07/16 02:45:33 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_redirections_exist(t_token **tokens)
{
	t_token	*tmp;

	tmp = *tokens;
	while (tmp->next != NULL)
	{
		if (tmp->type != NONE)
			return (TRUE);
		tmp = tmp->next;
	}
	return (FALSE);
}

int	ft_pipes_exist(t_token **tokens)
{
	t_token	*tmp;

	tmp = *tokens;
	while (tmp != NULL)
	{
		if (tmp->type == PIPE)
			return (TRUE);
		tmp = tmp->next;
	}
	return (FALSE);
}

void	ft_redirections_parse(t_token *tokens, t_cmd_list *cmd_list)
{
	int		fd_in;
	int		fd_out;
	int		**fd_list;
	char	**input;

	fd_list = ft_redirect_init(&tokens);
	if (fd_list == NULL)
		return ;
	fd_in = ft_get_fd(fd_list[0]);
	fd_out = ft_get_fd(fd_list[1]);
	input = ft_tokens_convert(tokens);
	if (input[0] != NULL)
		ft_add_cmd(cmd_list, input, fd_in, fd_out);
	ft_free_line(input);
	free(fd_list[0]);
	free(fd_list[1]);
	free(fd_list);
	ft_heredoc_remove(cmd_list);
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

void	ft_parser(char *line, t_env_v **env, t_cmd_list *cmd_list)
{
	t_token		*tokens;
	char		**input;

	//line = env_vars(line, env->env_v); //checks $$ at the end of the line (?)
	line = ft_remove_extra_spaces(line);
	tokens = ft_lexer(ft_split(line, ' '));
	if (line[0] != '\0' && ft_redirect_check(line) && ft_quotes_check(line))
	{
		ft_quotes_remove(&tokens, env);
		printf("%d\n", ft_pipes_exist(&tokens));
		if (ft_pipes_exist(&tokens) == TRUE)
		{
			printf("token_existance = %s\n", tokens->value);
			ft_pipe_parse(tokens, cmd_list);
		}
		else if (ft_redirections_exist(&tokens) == TRUE)
			ft_redirections_parse(tokens, cmd_list);
		else
		{
			input = ft_tokens_convert(tokens);
			if (input != NULL && input[0] != NULL)
				ft_add_cmd(cmd_list, input, 0, 1);
			if (input != NULL)
				ft_free_line(input);
		}
		ft_executer(cmd_list);
	}
	ft_tokens_free(tokens);
	free(line);
}
