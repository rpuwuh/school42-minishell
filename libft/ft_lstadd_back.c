/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 04:12:38 by eleon             #+#    #+#             */
/*   Updated: 2022/07/08 21:44:21 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*nextelem;

	if (new && lst)
	{
		if (!*lst)
		{
			*lst = new;
			return ;
		}
		nextelem = ft_lstlast(*lst);
		nextelem->next = new;
	}
}
