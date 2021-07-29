/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 14:46:41 by hbuck             #+#    #+#             */
/*   Updated: 2020/11/02 16:18:48 by hbuck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;
	char	sym;

	ptr = (char *)s + ft_strlen(s);
	sym = (char)c;
	while (ptr >= s)
	{
		if (*ptr == sym)
			return (ptr);
		ptr--;
	}
	return (NULL);
}
