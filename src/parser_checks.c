/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 23:13:26 by dmillan           #+#    #+#             */
/*   Updated: 2022/07/10 00:04:09 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_quotes_check(char *s)
{
	
}

static int	ft_redirect_check(char *s)
{
	if (check_pipes(s) == false)
	{
		ft_write_error(NULL, NULL, "parse error");
		return (false);
	}
	if (check_arrows(s, '<') == false || check_arrows(s, '>') == false)
	{
		ft_write_error(NULL, NULL, "parse error");
		return (false);
	}
	if (check_double_arrows(s, '<') == false
		|| check_double_arrows(s, '>') == false)
	{
		ft_write_error(NULL, NULL, "parse error");
		return (false);
	}
	return (true);
}
