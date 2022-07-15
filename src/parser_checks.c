/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 23:13:26 by dmillan           #+#    #+#             */
/*   Updated: 2022/07/15 03:39:37 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_cmd_or_file(char c)
{
	if (c > 32 && c < 127)
	{
		if (c != '|' && c != '>' && c != '<')
			return (TRUE);
		return (FALSE);
	}
	return (FALSE);
}

int	ft_pipes_parsecheck(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '|' && ft_quotes_open(s, i, '"', '\'') == FALSE)
		{
			i++;
			while (s[i] == ' ')
				i++;
			if (s[i] == '<' && s[i + 1] == '<')
				i += 2;
			else if (s[i] == '>' && s[i + 1] == '>')
				i += 2;
			else if (s[i] == '<' || s[i] == '>')
				i++;
			while (s[i] == ' ')
				i++;
			if (ft_cmd_or_file(s[i]) == TRUE)
				continue ;
			return (FALSE);
		}
		i++;
	}
	return (true);
}

static int	ft_arrows_parsecheck(char *s, char arr_symb)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (!ft_quotes_open(s, i, '"', '\'')
			&& s[i] == arr_symb && s[i + 1] != arr_symb)
		{
			i++;
			while (s[i] == ' ')
				i++;
			if (ft_cmd_or_file(s[i]) == TRUE)
				continue ;
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

int	ft_double_arrows_parsecheck(char *s, char arr_symb)
{
	int	i;

	i = 0;
	while (s[i + 1] != '\0')
	{
		if (s[i] == arr_symb && s[i + 1] == arr_symb)
		{
			i += 2;
			while (s[i] == ' ')
				i++;
			if (ft_cmd_or_file(s[i]) == TRUE)
				continue ;
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

int	ft_redirect_check(char *s)
{
	if (ft_pipes_parsecheck(s) == FALSE)
	{
		ft_exit_with_error("pipes", "parse error");
		return (FALSE);
	}
	if (ft_arrows_parsecheck(s, '<') == FALSE
		|| ft_arrows_parsecheck(s, '>') == FALSE)
	{
		ft_exit_with_error("< or >", "parse error");
		return (FALSE);
	}
	if (ft_double_arrows_parsecheck(s, '<') == FALSE
		|| ft_double_arrows_parsecheck(s, '>') == FALSE)
	{
		ft_exit_with_error("<< or >>", "parse error");
		return (FALSE);
	}
	return (TRUE);
}
