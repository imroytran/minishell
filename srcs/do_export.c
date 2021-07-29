/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 14:44:45 by hbuck             #+#    #+#             */
/*   Updated: 2021/07/27 16:27:56 by hbuck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_export_list(void)
{
	t_list		*temp;
	t_var_env	*content;

	sort_env_list();
	temp = g_mini.env_list;
	while (temp)
	{
		content = temp->content;
		if (content->value != NULL)
			printf("declare -x %s=\"%s\"\n", content->name, content->value);
		else
			printf("declare -x %s\n", content->name);
		temp = temp->next;
	}
}

void	add_env(char *env)
{
	t_list		*temp;
	t_var_env	*con;
	t_var_env	*tmp;

	temp = g_mini.env_list;
	con = make_content(env);
	if (con == NULL)
		return ;
	while (temp)
	{
		tmp = temp->content;
		if (!ft_strcmp(tmp->name, con->name))
		{
			if (con->value != NULL)
			{
				free_content(temp->content);
				temp->content = con;
			}
			else
				free_content(con);
			return ;
		}
		temp = temp->next;
	}
	ft_lstadd_back(&g_mini.env_list, ft_lstnew(con));
}

void	add_envs(char *envs[])
{
	int	i;

	i = 1;
	while (envs[i])
	{
		add_env(envs[i]);
		i++;
	}
}

int	do_export(char *argv[])
{
	g_mini.global_output = 0;
	if (argv[1] == NULL)
		print_export_list();
	else
	{
		add_envs(argv);
		sort_env_list();
	}
	return (g_mini.global_output);
}
