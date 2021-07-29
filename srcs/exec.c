#include "../includes/minishell.h"

static int	do_buildin(char **cmd)
{
	if (!ft_strcmp(cmd[0], "cd"))
		return (do_cd(cmd));
	else if (!ft_strcmp(cmd[0], "pwd"))
		return (do_pwd());
	else if (!ft_strcmp(cmd[0], "echo"))
		return (do_echo(cmd));
	else if (!ft_strcmp(cmd[0], "export"))
		return (do_export(cmd));
	else if (!ft_strcmp(cmd[0], "unset"))
		return (do_unset(cmd));
	else if (!ft_strcmp(cmd[0], "env"))
		return (do_env(cmd));
	else if (!ft_strcmp(cmd[0], "exit"))
		return (exit_buildin(cmd));
	return (0);
}

static void	set_inout(int in, int out, int cmd_in)
{
	if (cmd_in != 0)
	{
		dup2(cmd_in, 0);
		close(cmd_in);
	}
	else if (in != 0)
	{
		dup2(in, 0);
		close(in);
	}
	if (out != 1)
	{
		dup2(out, 1);
		close(out);
	}
}

static void	set_output(void)
{
	int	status;

	wait(&status);
	g_mini.is_fork = getpid();
	if (WIFEXITED(status))
		g_mini.global_output = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_mini.global_output = WTERMSIG(status) + 128;
}

static int	execute(int in, int out, t_cmd *t_cmd)
{
	char	**cmd;
	char	**env;

	cmd = t_cmd->cmd;
	env = NULL;
	if (check_builtins_not_pipe(cmd[0]))
		return (do_buildin(cmd));
	g_mini.is_fork = fork();
	if (g_mini.is_fork == 0)
	{
		increment_sh_lvl();
		env = lst_to_char();
		set_inout(in, out, t_cmd->fd_input);
		if (check_builtins(cmd[0]))
			exit(do_buildin(cmd));
		else
		{
			if (execve(cmd[0], cmd, env) < 0)
				return (print_erro_int(strerror(errno)) - 1);
		}
	}
	set_output();
	if (env)
		free_split(env);
	return (g_mini.global_output);
}

int	exec(t_list *commands)
{
	t_cmd	*cmd;
	int		fd[2];
	int		fdpipe[2];

	cmd = commands->content;
	fd[0] = cmd->fd_input;
	fd[1] = cmd->fd_out;
	while (commands->next)
	{
		cmd = commands->content;
		pipe(fdpipe);
		execute(fd[0], fdpipe[1], cmd);
		close(fdpipe[1]);
		fd[0] = fdpipe[0];
		commands = commands->next;
	}
	cmd = commands->content;
	return (execute(fd[0], fd[1], cmd));
}
