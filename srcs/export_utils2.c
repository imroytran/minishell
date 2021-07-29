/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 15:55:20 by hbuck             #+#    #+#             */
/*   Updated: 2021/07/26 13:34:14 by hbuck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	swap_content(t_list *min, t_list *tmp)
{
	void	*swap_content;

	swap_content = tmp->content;
	tmp->content = min->content;
	min->content = swap_content;
}

void	sort_env_list(void)
{
	t_list		*tmp;
	t_list		*top;
	t_var_env	*tmp_content;
	t_var_env	*env_content;

	top = g_mini.env_list;
	while ((top->next) != NULL)
	{
		tmp = top->next;
		while (tmp != NULL)
		{
			tmp_content = tmp->content;
			env_content = top->content;
			if (ft_strcmp(tmp_content->name, env_content->name) < 0)
				swap_content(tmp, top);
			tmp = tmp->next;
		}
		top = top->next;
	}
}

int	is_bad_var_name(char *name)
{
	int	i;

	i = 0;
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (1);
	while (name[i])
	{
		if (!ft_isalpha(name[i]) && name[i] != '_' && !ft_isdigit(name[i]))
			return (1);
		i++;
	}
	return (0);
}
