/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 00:41:41 by dmillan           #+#    #+#             */
/*   Updated: 2022/07/16 01:14:10 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_read_until_heredoc(char *delimiter)
{
	char	*input;
	char	*tmp;

	input = (char *)malloc(sizeof(char));
	if (input == NULL)
		return (NULL);
	while (1)
	{
		tmp = readline(YELLOW"> "RESETCOLOR);
		if (ft_strcmp(tmp, delimiter) == 0)
		{
			free(tmp);
			break ;
		}
		if (tmp != NULL && input != NULL)
		{
			tmp = ft_strjoin(tmp, "\n");
			input = ft_strjoin(input, tmp);
			free(tmp);
		}
	}
	return (input);
}

int	ft_redirections_count(t_token *tokens, int type_a, int type_b)
{
	int		i;
	t_token	*tmp;

	tmp = tokens;
	i = 0;
	while (tmp != NULL)
	{
		if ((int)tmp->type == type_a || (int)tmp->type == type_b)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

static void	ft_create_heredoc(t_token *tmp, int *fd_list, int i)
{
	char	*heredoc;
	int		fd;

	heredoc = ft_read_until_heredoc(tmp->next->value);
	fd = open("heredoc", O_RDWR | O_CREAT | O_TRUNC, 0777);
	write (fd, heredoc, ft_strlen(heredoc));
	close(fd);
	free(heredoc);
	fd_list[i] = ft_redirect("heredoc", HEREDOC);
}

int	ft_fd_list_check(t_token *tokens,
		int type_a, int type_b, int *fd_list)
{
	int		i;
	t_token	*tmp;

	tmp = tokens;
	i = 0;
	while (tmp != NULL)
	{
		if ((int)tmp->type == type_a || (int)tmp->type == type_b)
		{
			if (tmp->type == HEREDOC)
				ft_create_heredoc(tmp, fd_list, i);
			else
				fd_list[i] = ft_redirect(tmp->next->value, tmp->type);
			if (fd_list[i] == -1)
				return (FALSE);
			i++;
		}
		tmp = tmp->next;
	}
	fd_list[i] = -1;
	return (TRUE);
}

int	**ft_redirect_init(t_token **token_list)
{
	int		**fd_list;
	int		i;
	int		check;
	t_token	*tokens;

	tokens = *token_list;
	fd_list = (int **)malloc(2 * sizeof(int *));
	if (fd_list == NULL)
		return (NULL);
	i = ft_redirections_count(tokens, INPUT, HEREDOC);
	fd_list[0] = (int *)malloc((i + 1) * sizeof(int));
	i = ft_redirections_count(tokens, TRUNC, APPEND);
	fd_list[1] = (int *)malloc((i + 1) * sizeof(int));
	if (fd_list[0] == NULL || fd_list[1] == NULL)
		return (NULL);
	check = ft_fd_list_check(tokens, INPUT, HEREDOC, fd_list[0]);
	if (check == TRUE)
		check = ft_fd_list_check(tokens, TRUNC, APPEND, fd_list[1]);
	if (check == FALSE)
	{
		free(fd_list[0]);
		free(fd_list[1]);
		free(fd_list);
		return (NULL);
	}
	printf("check = true\n");
	return (fd_list);
}
