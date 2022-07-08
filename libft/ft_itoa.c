/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 22:29:15 by dmillan           #+#    #+#             */
/*   Updated: 2021/10/26 01:14:17 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_getlength(int n)
{
	int	count;

	count = 0;
	if (n <= 0)
		count++;
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static char	*ft_fillstr(char *str, int len, unsigned int nbr)
{
	str[len--] = '\0';
	while (len >= 0)
	{
		str[len] = nbr % 10 + '0';
		nbr /= 10;
		len--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	unsigned int	nbr;
	int				sign;
	int				len;
	char			*str;

	if (n < 0)
	{
		nbr = -n;
		sign = 1;
	}
	else
	{
		nbr = n;
		sign = 0;
	}
	len = ft_getlength(n);
	str = (char *)malloc(sizeof(char) * len + 1);
	if (str == NULL)
		return (NULL);
	str = ft_fillstr(str, len, nbr);
	if (sign == 1)
		str[0] = '-';
	return (str);
}
