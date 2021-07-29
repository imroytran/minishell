#include "../includes/minishell.h"

static void	get_heredoc(t_cmd *cmd, char *delimited)
{
	char	*buff;
	char	*temp;

	pipe(cmd->fdpipe);
	while (1)
	{
		buff = readline("> ");
		if (!delimited)
			break ;
		if (!ft_strcmp(delimited, buff))
		{
			free(buff);
			break ;
		}
		temp = get_arg(buff);
		free(buff);
		ft_putstr_fd(temp, cmd->fdpipe[1]);
		ft_putchar_fd('\n', cmd->fdpipe[1]);
		if (temp)
			free(temp);
	}
	close(cmd->fdpipe[1]);
	if (cmd->fd_input != 0)
		close(cmd->fd_input);
	cmd->fd_input = cmd->fdpipe[0];
}

static char	*get_inpfile(char **arg, char *text_inp, int flag)
{
	int		i;
	int		j;
	char	*check;
	char	*temp;

	i = 0;
	j = 0;
	temp = *arg;
	if (flag > 2)
		return (print_error_syntax(flag, '<'));
	if (!check_closed_quotes(text_inp))
		return (print_erro(ERR_UNCL_QT, NULL));
	while (*temp && ft_strchr(" \t\'\"", *temp) && !check_inside(text_inp, temp))
	{
		j++;
		temp++;
	}
	if (*temp == '\0')
		return ((char *)print_erro(ERR_TOKEN_NEWL, NULL));
	while (*temp && (!ft_strchr(">< \t\'\"", temp[i]) || (ft_strchr(">< \t\'\"", \
		temp[i]) && check_inside(text_inp, temp + i))))
		i++;
	check = ft_substr(temp, 0, i);
	*arg += i + j;
	return (check);
}

static int	get_fd(t_cmd *cmd, int flag, int flag_out, char *check)
{
	char	*file;

	file = get_arg(check);
	if (!file)
		return (print_erro_int(ERR_SUCH_FD));
	if (cmd->fd_input != 0)
	{
		close (cmd->fd_input);
		cmd->fd_input = 0;
	}
	if (flag == 1)
	{
		if (flag_out <= 2)
			cmd->fd_input = open(file, O_RDONLY);
	}
	else if (flag == 2)
		get_heredoc(cmd, check);
	free(file);
	return (1);
}

int	get_fdin(t_cmd *cmd, int flag_out, char *input)
{
	char	*temp;
	char	*check;
	int		flag;

	temp = input;
	while (*temp)
	{
		if (*temp == '<' && !check_inside(input, temp))
		{
			flag = 0;
			while (*temp++ == '<')
				flag++;
			temp--;
			check = get_inpfile(&temp, input, flag);
			if (!check)
				return (0);
			if (!get_fd(cmd, flag, flag_out, check))
				return (0);
			free(check);
			continue ;
		}
		temp++;
	}
	return (1);
}
