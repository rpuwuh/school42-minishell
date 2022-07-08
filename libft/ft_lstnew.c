/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleon <eleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 04:09:39 by eleon             #+#    #+#             */
/*   Updated: 2021/10/25 17:14:35 by eleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*newlist;

	newlist = (t_list *)malloc(sizeof(t_list));
	if (!newlist)
		return (NULL);
	newlist->content = content;
	newlist->next = NULL;
	return (newlist);
}
