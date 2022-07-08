/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 21:36:29 by dmillan           #+#    #+#             */
/*   Updated: 2022/07/08 21:36:40 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*b1;
	unsigned char	*b2;

	if (s1 == NULL || s2 == NULL)
		return (-1);
	b1 = (unsigned char *)s1;
	b2 = (unsigned char *)s2;
	while (*b1 == *b2 && *b1 != '\0')
	{
		b1++;
		b2++;
	}
	if (*b1 == *b2)
		return (0);
	else
		return (*b1 - *b2);
}
