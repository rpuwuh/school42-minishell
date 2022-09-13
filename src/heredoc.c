/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 00:05:19 by dmillan           #+#    #+#             */
/*   Updated: 2022/09/14 00:07:24 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_sig_empty(int sig)
{
	(void)sig;
	write(1, "\n", 1);
}

void	ft_sig_heredoc(int sig)
{
	(void)sig;
	exit(1);
}

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
		signal(SIGINT, ft_sig_empty);
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

void	ft_create_heredoc(t_token *tmp, int *fd_list, int i)
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
