/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 12:38:57 by hbuck             #+#    #+#             */
/*   Updated: 2020/11/09 13:46:49 by hbuck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	i;

	if (!dst)
		return (0);
	src_len = ft_strlen(src);
	i = 0;
	if (dstsize == 0)
		return (src_len);
	while (src[i] != '\0' && (dstsize - 1) > i)
	{
		dst[i] = src[i];
		++i;
	}
	dst[i] = '\0';
	return (src_len);
}
