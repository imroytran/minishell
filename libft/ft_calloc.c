/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 14:34:47 by hbuck             #+#    #+#             */
/*   Updated: 2020/11/09 15:43:03 by hbuck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*addr;

	addr = (void *)malloc(count * size);
	if (addr)
		ft_memset(addr, 0, count * size);
	return (addr);
}
