/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 18:07:40 by hbuck             #+#    #+#             */
/*   Updated: 2021/04/25 20:50:13 by hbuck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	size_t			i;
	unsigned long	res;
	int				negative;

	i = 0;
	while (str[i] != '\0' && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
		i++;
	res = 0;
	negative = 1;
	if (str[i] == '-')
		negative *= -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - 48);
		if ((long)(negative * res) > 2147483647)
			return (-1);
		if ((long)(negative * res) < -2147483648)
			return (0);
		i++;
	}
	return ((int)(res * negative));
}
