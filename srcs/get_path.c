#include "../includes/minishell.h"

int	check_builtins_not_pipe(char *command)
{
	if (!ft_strcmp(command, "cd") || !ft_strcmp(command, "export")
		|| !ft_strcmp(command, "unset") || !ft_strcmp(command, "exit")
		|| !ft_strcmp(command, "env"))
		return (1);
	return (0);
}

static int	get_binar(char *path, char **arg)
{
	char		*temp;
	char		*temp2;
	struct stat	stats;

	temp = ft_strjoin(path, "/");
	if (!temp)
		return (print_erro_int("ERROR: Malloc"));
	temp2 = ft_strjoin(temp, *arg);
	if (!temp2)
		return (print_erro_int("ERROR: Malloc"));
	free(temp);
	if (!stat(temp2, &stats))
	{
		free(*arg);
		*arg = temp2;
		return (1);
	}
	free(temp2);
	return (0);
}

static int	change_path(char **arg, char *path)
{
	char	**split;
	int		i;

	if (check_builtins(arg[0]))
		return (1);
	split = ft_split(path, ':');
	if (!split)
		return (print_erro_int("ERROR: Malloc"));
	i = 0;
	while (split[i])
	{
		if (get_binar(split[i], arg))
			return (1);
		i++;
	}
	printf("minishell: %s: command not found\n", *arg);
	g_mini.global_output = 127;
	return (0);
}

int	check_path(char **arg)
{
	char		*temp;
	struct stat	stats;

	temp = *arg;
	if (ft_strchr(temp, '/'))
	{
		if (!stat(temp, &stats))
			return (1);
		printf("minishell: %s: No such file or directory\n", temp);
		g_mini.global_output = 127;
	}
	else
	{
		temp = ft_getenv("PATH");
		if (temp == NULL)
		{
			printf("minishell: %s: command not found\n", *arg);
			g_mini.global_output = 127;
			return (0);
		}
		else if (!change_path(arg, temp))
			return (0);
	}
	return (1);
}
