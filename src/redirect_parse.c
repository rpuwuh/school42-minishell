/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 00:49:31 by dmillan           #+#    #+#             */
/*   Updated: 2022/08/18 03:17:38 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_heredoc_remove(t_cmd_list *cmd_list)
{
	char	**tmp;

	if (access("heredoc", F_OK) == 0)
	{
		tmp = (char **)malloc(3 * sizeof(char *));
		tmp[2] = NULL;
		tmp[0] = ft_strdup("rm");
		tmp[1] = ft_strdup("heredoc");
		ft_add_cmd(cmd_list, tmp, 0, 1);
		ft_free_line(tmp);
	}
}

void	reset_fd(int og_fd, char *operator)
{
	if (ft_strcmp(operator, "<") == 0)
		dup2(STDIN_FILENO, og_fd);
	else if (ft_strcmp(operator, ">") == 0 || ft_strcmp(operator, ">>") == 0)
		dup2(STDOUT_FILENO, og_fd);
}

static int	ft_return_fd_input(char *filename, int fd)
{
	fd = access(filename, F_OK);
	if (fd == -1)
	{
		ft_exit_with_error(filename, "No such file or directory");
		return (-1);
	}
	fd = open(filename, O_RDONLY, 0777);
	if (fd == -1)
	{
		ft_exit_with_error(filename, "Permission denied");
		return (-1);
	}
	printf("fd_in = %d\n", fd);
	return (fd);
}

static int	ft_return_fd_output(char *filename, int fd)
{
	fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		ft_exit_with_error(filename, "Permission denied");
		return (-1);
	}
	printf("fd_out_redir = %d\n", fd);
	return (fd);
}

int	ft_redirect(char *filename, int type)
{
	int	fd;

	fd = 0;
	if (type == INPUT || type == HEREDOC)
		return (ft_return_fd_input(filename, fd));
	else if (type == TRUNC)
		return (ft_return_fd_output(filename, fd));
	else if (type == APPEND)
	{
		fd = open(filename, O_RDWR | O_CREAT | O_APPEND, 0777);
		if (fd == -1)
		{
			ft_exit_with_error(filename, "Permission denied");
			return (-1);
		}
		return (fd);
	}
	return (-1);
}
