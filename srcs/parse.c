#include "../includes/minishell.h"

static char	**get_argv(char **argv, char **line, int *argc)
{
	char	**temp;
	size_t	i;

	temp = malloc(sizeof(char *) * (*argc + 2));
	if (!temp)
		return (print_erro(strerror(errno), NULL));
	if (!move_arr(argv, temp, argc))
		return (NULL);
	i = get_newarg(temp, line, argc);
	if (!i)
		return (NULL);
	temp[*argc] = NULL;
	*line += i - 1;
	return (temp);
}

static void	deleted_rdr(char **line)
{
	char	*temp;
	int		i;

	i = 0;
	temp = *line;
	while (*temp && ft_strchr(">< \t", *temp))
	{
		temp++;
		i++;
	}
	while (*temp && (!ft_strchr(" \t><", *temp)
			|| (ft_strchr(" \t><", *temp) && check_inside(temp - i, temp))))
	{
		temp++;
		i++;
	}
	*line += i;
}

static char	**get_simple_command(char *line)
{
	int		argc;
	char	*temp;
	char	**argv;

	temp = line;
	argc = 0;
	argv = NULL;
	while (*temp)
	{
		if (*temp != ' ' && *temp != '\t')
		{
			if (*temp == '>' || *temp == '<')
			{
				deleted_rdr(&temp);
				continue ;
			}
			argv = get_argv(argv, &temp, &argc);
			if (!argv)
				return (NULL);
		}
		temp++;
	}
	return (argv);
}

static int	add_simp_cmd(char *pipe, t_list **temp)
{
	t_cmd	*cmd;

	if (!check_closed_quotes(pipe))
		return (print_erro_int(ERR_UNCL_QT));
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (print_erro_int(strerror(errno)));
	cmd->cmd = get_simple_command(pipe);
	if (!cmd->cmd)
	{
		free(cmd);
		return (0);
	}
	if (!redirect(pipe, cmd))
		return (0);
	ft_lstadd_back(temp, ft_lstnew(cmd));
	return (1);
}

int	get_parse(t_list **commands, char *line)
{
	char	**pipes;
	t_list	*temp;
	int		i;

	temp = NULL;
	pipes = ft_split_outside(line, '|');
	if (!pipes)
		return (0);
	i = 0;
	while (pipes[i])
	{
		if (!add_simp_cmd(pipes[i], &temp))
		{
			ft_lstclear(commands, &del_argv);
			return (free_split(pipes));
		}
		i++;
	}
	*commands = temp;
	free_split(pipes);
	return (1);
}
