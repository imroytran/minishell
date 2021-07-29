/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 11:24:37 by hbuck             #+#    #+#             */
/*   Updated: 2021/07/27 15:58:34 by hbuck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	increment_sh_lvl(void)
{
	int			shlvl;
	t_list		*list;
	t_var_env	*content;

	list = find_env("SHLVL");
	content = list->content;
	shlvl = ft_atoi(content->value);
	shlvl++;
	free(content->value);
	content->value = ft_itoa(shlvl);
}

int	do_env(char **cmd)
{
	t_list		*temp;
	t_var_env	*temp_content;

	temp = g_mini.env_list;
	if (cmd[1] != NULL)
	{
		printf("env: %s: No such file or directory\n", cmd[1]);
		g_mini.global_output = 127;
		return (g_mini.global_output);
	}
	while (temp)
	{
		temp_content = temp->content;
		if (temp_content->value != NULL)
			printf("%s=%s\n", temp_content->name, temp_content->value);
		temp = temp->next;
	}
	g_mini.global_output = 0;
	return (g_mini.global_output);
}
