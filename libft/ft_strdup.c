/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 19:43:53 by dmillan           #+#    #+#             */
/*   Updated: 2021/10/26 02:37:49 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static char	*ft_strcpy(char	*dest, const char	*src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(const char *s1)
{
	size_t		length;
	char		*dest;

	length = ft_strlen(s1);
	dest = (char *)malloc(sizeof(char) * (length + 1));
	if (dest == NULL)
		return (NULL);
	dest = ft_strcpy(dest, s1);
	return (dest);
}
