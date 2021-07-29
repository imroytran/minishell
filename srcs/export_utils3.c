/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jregenia <jregenia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 17:15:47 by jregenia          #+#    #+#             */
/*   Updated: 2021/07/26 16:06:05 by jregenia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	export_unset_error(char *name, char *command)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": \'", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd("\': not a valid identifier\n", 2);
	g_mini.global_output = 1;
}

void	get_value(t_var_env *content, char *env, int i)
{
	char	*temp;

	temp = ft_substr(env, i + 1, ft_strlen(env) - i - 1);
	if (temp == NULL)
	{
		free(content->name);
		free(content);
		do_exit(1);
	}
	content->value = temp;
}

void	get_name(t_var_env *content, char *env, int i)
{
	char	*temp;

	temp = ft_substr(env, 0, i);
	if (temp == NULL)
	{
		free(content);
		do_exit(1);
	}
	content->name = temp;
}

t_var_env	*make_content(char *env)
{
	int			i;
	t_var_env	*content;

	i = 0;
	content = malloc(sizeof(t_var_env));
	if (content == NULL)
		do_exit(1);
	while (env[i] && env[i] != '=')
		i++;
	get_name(content, env, i);
	if (is_bad_var_name(content->name) == 1)
	{
		export_unset_error(content->name, "export");
		free_content(content);
		return (NULL);
	}
	if (env[i] == '=')
		get_value(content, env, i);
	else
		content->value = NULL;
	return (content);
}
