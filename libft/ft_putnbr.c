/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 23:18:38 by dmillan           #+#    #+#             */
/*   Updated: 2021/10/08 23:28:12 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//KOed last time!

#include <unistd.h>

void	ft_putchar(char c)
{
	write (1, &c, 1);
}

void	ft_getrray(int x[], int nb)
{
	int	i;
	int	num;

	num = nb;
	i = 9;
	while (i >= 0)
	{
		x[i] = num % 10;
		num /= 10;
		i--;
	}
}

int	ft_getsize(int nb)
{
	int	number;
	int	count;

	count = 1;
	number = nb;
	while (number / 10 != 0)
	{
		number /= 10;
		count++;
	}
	return (count);
}

void	ft_putnbr(int nb)
{
	int	x[10];
	int	size;

	if (nb == -2147483648)
	{
		ft_putchar('-');
		ft_putchar('2');
		nb = 147483648;
	}
	else if (nb < 0)
	{
		ft_putchar('-');
		nb = -nb;
	}
	size = ft_getsize(nb);
	ft_getrray(x, nb);
	while (size > 0)
	{
		ft_putchar(x[10 - size] + 48);
		size--;
	}
	ft_putchar('\n');
}
