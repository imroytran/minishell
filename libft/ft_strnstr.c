/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 13:41:16 by hbuck             #+#    #+#             */
/*   Updated: 2020/11/13 15:53:37 by hbuck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (haystack == needle || (*needle == '\0' && len == 0))
		return ((char *)haystack);
	i = 0;
	while (haystack[i] && i <= len)
	{
		j = 0;
		while (haystack[i] == needle[j] && haystack[i] && needle[j] && i < len)
		{
			j++;
			i++;
		}
		if (!needle[j] && i - j < len)
			return ((char *)haystack + i - j);
		i++;
	}
	return (NULL);
}
