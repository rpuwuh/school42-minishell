/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 03:20:12 by eleon             #+#    #+#             */
/*   Updated: 2022/09/07 22:36:46 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_emptystr(char *dst)
{
	dst = malloc(sizeof(char));
	if (dst == NULL)
		return (NULL);
	dst[0] = '\0';
	return (dst);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dst;
	size_t	i;

	dst = NULL;
	if (s == NULL)
		return (NULL);
	if (ft_strlen(s) < start)
		return (ft_emptystr(dst));
	else
	{
		if (start + len > ft_strlen(s))
			len = ft_strlen(s) - start;
		dst = malloc(sizeof(char) * (len + 1));
		if (dst == NULL)
			return (NULL);
		i = -1;
		while (++i < len)
			*(dst + i) = *(s + start + i);
		*(dst + i) = '\0';
		return (dst);
	}
}
