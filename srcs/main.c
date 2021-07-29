#include "../includes/minishell.h"

int	minishell(char *line)
{
	t_list		*commands;
	int			status;

	status = get_parse(&commands, line);
	if (!status)
		return (-1);
	g_mini.global_output = exec(commands);
	ft_lstclear(&commands, &del_argv);
	return (g_mini.global_output);
}

int	get_commands(void)
{
	char	*line;

	while (1)
	{
		line = NULL;
		line = readline("minishell:> ");
		if (!line || *line == '\4' || *line == EOF)
		{
			if (line)
				free(line);
			ft_putstr_fd("\033[Aminishell:> exit\n", 1);
			do_exit(0);
		}
		else
		{
			if (*line)
			{
				add_history(line);
				minishell(line);
				rl_on_new_line();
			}
		}
	}
	return (g_mini.global_output);
}

void	setup_term(void)
{
	struct termios	mini;

	tcgetattr(0, &mini);
	mini.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &mini);
}

int	main(int argc, char **argv, char *env[])
{
	(void) argc;
	(void) argv;
	init_env_list(env);
	if (!g_mini.env_list)
		return (0);
	g_mini.is_fork = 0;
	g_mini.start_pid = getpid();
	g_mini.global_output = 0;
	setup_term();
	signal(SIGQUIT, our_sig_proc);
	signal(SIGINT, our_sig_proc);
	return (get_commands());
}
