/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 22:45:27 by dmillan           #+#    #+#             */
/*   Updated: 2021/10/26 00:15:04 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int				i;
	int				sign;
	long			res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if ((((res * 10) + (str[i] - '0')) < res) && (sign == 1))
			return (-1);
		else if ((((res * 10) + (str[i] - '0')) < res) && (sign == -1))
			return (0);
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return ((int)(res * sign));
}
