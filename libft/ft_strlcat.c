/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 20:42:56 by dmillan           #+#    #+#             */
/*   Updated: 2021/10/26 02:30:18 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	d_len;

	i = 0;
	d_len = ft_strlen(dest);
	if (size <= d_len)
		return (size + ft_strlen(src));
	while ((src[i] != '\0') && (d_len < (size - 1)))
	{
		dest[d_len] = src[i];
		d_len++;
		i++;
	}
	dest[d_len] = '\0';
	return (d_len + ft_strlen(&src[i]));
}
