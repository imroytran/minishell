/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 12:13:29 by hbuck             #+#    #+#             */
/*   Updated: 2021/04/16 12:33:23 by hbuck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_free_arr(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

static size_t	ft_count_words(char const *s, char c)
{
	size_t	i;
	size_t	count;

	if (!s[0])
		return (0);
	i = 0;
	count = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c)
		{
			count++;
			while (s[i] && s[i] == c)
				i++;
			continue ;
		}
		i++;
	}
	if (s[i - 1] != c)
		count++;
	return (count);
}

static void	ft_get_next_word(char **arr, size_t *str_len, char c)
{
	size_t	i;

	*arr += *str_len;
	*str_len = 0;
	i = 0;
	while (**arr && **arr == c)
		(*arr)++;
	while ((*arr)[i])
	{
		if ((*arr)[i] == c)
			return ;
		(*str_len)++;
		i++;
	}
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	char	*word;
	size_t	str_len;
	size_t	count_words;
	size_t	i;

	if (!s)
		return (NULL);
	count_words = ft_count_words(s, c);
	arr = (char **)malloc(sizeof(char *) * (count_words + 1));
	if (arr == NULL)
		return (NULL);
	i = 0;
	word = (char *)s;
	str_len = 0;
	while (i < count_words)
	{
		ft_get_next_word(&word, &str_len, c);
		arr[i] = (char *)malloc(sizeof(char) * (str_len + 1));
		if (arr[i] == NULL)
			return (ft_free_arr(arr));
		ft_strlcpy(arr[i++], word, str_len + 1);
	}
	arr[i] = NULL;
	return (arr);
}
