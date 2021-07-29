/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 15:05:34 by hbuck             #+#    #+#             */
/*   Updated: 2021/04/16 12:38:40 by hbuck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	while (s1[i] != '\0')
		i++;
	str = (char *)malloc((i + 1) * sizeof(*str));
	if (!str)
		return ((void *)0);
	while (j < i)
	{
		str[j] = s1[j];
		j++;
	}
	str[i] = '\0';
	return (str);
}
