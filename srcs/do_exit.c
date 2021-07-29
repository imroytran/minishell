/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jregenia <jregenia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 15:56:56 by hbuck             #+#    #+#             */
/*   Updated: 2021/07/27 17:59:13 by jregenia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exit_buildin(char **argv)
{
	if (argv[1] != NULL)
		printf("exit\nminishell: exit: %s: numeric argument required\n", argv[1]);
	return (do_exit(0));
}

int	do_exit(int error_nb)
{
	ft_lstclear(&g_mini.env_list, free_content);
	g_mini.global_output = error_nb;
	exit(error_nb);
	return (error_nb);
}

void	our_sig_proc(int sig)
{
	if (sig == SIGINT)
	{
		if (g_mini.is_fork == 0 || g_mini.is_fork == g_mini.start_pid)
		{
			write(1, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
			g_mini.global_output = 1;
		}
		else
			ft_putstr_fd("^C\n", 1);
	}
	else if (sig == SIGQUIT)
	{
		if (g_mini.is_fork == 0 || g_mini.is_fork == g_mini.start_pid)
		{
			rl_on_new_line();
			rl_redisplay();
			g_mini.global_output = 127;
		}
		else
			ft_putstr_fd("^\\Quit: 3\n", 1);
	}
}
