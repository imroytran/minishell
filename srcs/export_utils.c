/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 14:46:52 by hbuck             #+#    #+#             */
/*   Updated: 2021/07/27 16:05:44 by hbuck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*ptr1;
	unsigned char	*ptr2;
	size_t			i;

	ptr1 = (unsigned char *)s1;
	ptr2 = (unsigned char *)s2;
	i = 0;
	while (ptr1[i] || ptr2[i])
	{
		if (ptr1[i] != ptr2[i])
			return (ptr1[i] - ptr2[i]);
		i++;
	}
	return (0);
}

char	*ft_getenv(char *name)
{
	t_list		*temp;
	t_var_env	*content;

	temp = find_env(name);
	if (temp == NULL)
		return (NULL);
	content = temp->content;
	return (content->value);
}

int	init_env_list(char *env[])
{
	int			i;
	t_var_env	*content;
	t_list		*new;
	t_list		*envlist;

	i = 0;
	envlist = NULL;
	while (env[i])
	{
		content = make_content(env[i]);
		new = ft_lstnew(content);
		if (new == NULL)
			do_exit(1);
		ft_lstadd_back(&envlist, new);
		i++;
	}
	g_mini.env_list = envlist;
	return (1);
}

char	*do_char_from_lst(t_list *temp)
{
	t_var_env	*temp_content;
	char		*name;
	char		*env;

	temp_content = temp->content;
	if (temp_content->value == NULL)
	{
		env = ft_strdup(temp_content->name);
		if (env == NULL)
			do_exit(1);
	}
	else
	{
		name = ft_strjoin(temp_content->name, "=");
		if (name == NULL)
			do_exit(1);
		env = ft_strjoin(name, temp_content->value);
		free(name);
		if (env == NULL)
			do_exit(1);
	}
	return (env);
}

char	**lst_to_char(void)
{
	char		**env;
	t_list		*temp;
	int			i;

	i = 0;
	temp = g_mini.env_list;
	env = malloc(sizeof(char *) * (ft_lstsize(temp) + 1));
	if (env == NULL)
		do_exit(1);
	env[ft_lstsize(temp)] = NULL;
	while (i < ft_lstsize(g_mini.env_list))
	{
		env[i] = do_char_from_lst(temp);
		temp = temp->next;
		i++;
	}
	return (env);
}
