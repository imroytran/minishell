#include "../includes/minishell.h"

int	check_inside(char *line, const char *redir)
{
	char	*start1;
	char	*start2;
	char	*end1;
	char	*end2;

	start1 = ft_strchr(line, '\'');
	end1 = ft_strrchr(line, '\'');
	start2 = ft_strchr(line, '\"');
	end2 = ft_strrchr(line, '\"');
	if (start1)
	{
		if (redir - start1 > 0 && redir - end1 < 0)
			return (1);
		else
			return (0);
	}
	if (start2)
	{
		if (redir - start2 > 0 && redir - end2 < 0)
			return (1);
		else
			return (0);
	}
	return (0);
}

int	check_closed_quotes(const char *arg)
{
	char	temp;
	int		check;
	int		i;

	check = 1;
	temp = 0;
	i = 0;
	while (arg[i])
	{
		if (i > 0 && arg[i - 1] == '\\' && (arg[i] == '\''
				|| arg[i - 1] == '\"'))
			i++;
		if ((arg[i] == '\'' || arg[i] == '\"') && check == 1)
		{
			temp = arg[i];
			check = 0;
		}
		else if (!check && arg[i] == temp)
			check = 1;
		i++;
	}
	return (check);
}

int	check_builtins(char *command)
{
	if (!ft_strcmp(command, "cd") || !ft_strcmp(command, "echo")
		|| !ft_strcmp(command, "pwd") || !ft_strcmp(command, "export")
		|| !ft_strcmp(command, "unset") || !ft_strcmp(command, "env")
		|| !ft_strcmp(command, "exit"))
		return (1);
	return (0);
}
