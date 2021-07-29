/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_outside.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jregenia <jregenia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 17:16:02 by jregenia          #+#    #+#             */
/*   Updated: 2021/07/27 13:55:27 by jregenia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*print_erro(char *err, char *to_free)
{
	if (to_free)
		free(to_free);
	ft_putstr_fd(err, 2);
	ft_putchar_fd('\n', 2);
	return (NULL);
}

int	move_arr(char **arr, char **temp, int *count)
{
	int	i;

	i = 0;
	while (i < *count)
	{
		temp[i] = ft_strdup(arr[i]);
		if (!temp[i])
		{
			while (i--)
				free(temp[i]);
			free(temp);
			print_erro("ERROR: Malloc", NULL);
			return (0);
		}
		free(arr[i]);
		i++;
	}
	if (!arr)
		free(arr);
	return (1);
}

static char	**get_arr(char **arr, char **str, int *count)
{
	char	**temp;
	char	*split;
	size_t	i;

	temp = malloc(sizeof(char *) * (*count + 2));
	if (!temp)
		return (print_erro("ERROR: Malloc", NULL));
	if (!move_arr(arr, temp, count))
		return (NULL);
	i = 0;
	split = *str;
	while (split[i] != '\0' && (split[i] != '|'
			|| (split[i] == '|' && check_inside(split, split + i))))
		i++;
	temp[*count] = ft_substr(split, 0, i);
	*count += 1;
	temp[*count] = NULL;
	*str += i;
	return (temp);
}

char	**ft_split_outside(char *str, char c)
{
	int		count;
	char	*temp;
	char	**arr;

	count = 0;
	temp = str;
	arr = NULL;
	while (*temp && (*temp == ' ' || *temp == '\t'))
		temp++;
	if (*temp == c)
		return (print_erro(ERR_TOKEN_PIPE, NULL));
	while (*temp)
	{
		if (*temp && *temp != c)
		{
			arr = get_arr(arr, &temp, &count);
			if (!arr)
				return (NULL);
		}
		else
			temp++;
	}
	return (arr);
}
