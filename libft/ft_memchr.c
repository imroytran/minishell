/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 12:20:13 by hbuck             #+#    #+#             */
/*   Updated: 2021/04/16 12:38:58 by hbuck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*p;
	unsigned char	sym;

	p = (unsigned char *)s;
	sym = (unsigned char)c;
	while (n--)
	{
		if (*p == sym)
			return (p);
		p++;
	}
	return (NULL);
}
