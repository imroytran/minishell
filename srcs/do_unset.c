/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jregenia <jregenia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 14:49:17 by hbuck             #+#    #+#             */
/*   Updated: 2021/07/26 16:03:05 by jregenia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_value_from_list(t_list *env)
{
	t_var_env	*env_content;

	env_content = env->content;
	return (env_content->value);
}

t_list	*find_env(char *name)
{
	t_list		*temp;
	t_var_env	*temp_content;

	temp = g_mini.env_list;
	while (temp != NULL)
	{
		temp_content = temp->content;
		if (!ft_strcmp(name, temp_content->name))
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

void	free_content(void *content)
{
	t_var_env	*to_delete;

	to_delete = content;
	if (to_delete)
	{
		if (to_delete->name)
			free(to_delete->name);
		if (to_delete->value)
			free(to_delete->value);
		free(to_delete);
	}
}

void	find_and_del_lst(char *name)
{
	t_list		*temp;
	t_list		*tmp;

	temp = g_mini.env_list;
	tmp = find_env(name);
	while (temp != NULL && tmp != NULL)
	{
		if (temp == tmp || temp->next == tmp)
		{
			if (temp == tmp)
				g_mini.env_list = tmp->next;
			else if (temp->next == tmp)
				temp->next = tmp->next;
			ft_lstdelone(tmp, free_content);
			return ;
		}
		temp = temp->next;
	}
}

int	do_unset(char *argv[])
{
	int		i;

	i = 1;
	while (argv[i])
	{
		if (is_bad_var_name(argv[i]) == 1)
			export_unset_error(argv[i], "unset");
		else
			find_and_del_lst(argv[i]);
		i++;
	}
	return (0);
}
