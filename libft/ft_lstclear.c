/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 16:40:37 by hbuck             #+#    #+#             */
/*   Updated: 2020/11/11 17:33:35 by hbuck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*nextlst;

	if (!lst)
		return ;
	if (del)
	{
		while (*lst)
		{
			nextlst = *lst;
			*lst = nextlst->next;
			del(nextlst->content);
			free(nextlst);
		}
		*lst = NULL;
	}
}
