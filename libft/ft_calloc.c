/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 03:11:48 by eleon             #+#    #+#             */
/*   Updated: 2021/10/26 01:01:18 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	length;
	void	*dest;

	length = count * size;
	dest = malloc(length);
	if (dest == NULL)
		return (NULL);
	ft_memset(dest, 0, length);
	return (dest);
}
