#include "../includes/minishell.h"

static char	*get_outfile(char **arg, char *text)
{
	int		i;
	int		j;
	char	*check;
	char	*file;
	char	*temp;

	i = 0;
	j = 0;
	temp = *arg;
	while (*temp && (*temp == '>' || *temp == ' ' || *temp == '\t')
		&& !check_inside(text, temp))
	{
		j++;
		temp++;
	}
	while (!ft_strchr(">< \t", temp[i]) || (ft_strchr(">< \t", temp[i])
			&& check_inside(text, temp + i)))
		i++;
	check = ft_substr(temp, 0, i);
	if (*check == '\0' || !check)
		return (print_erro(ERR_TOKEN_NEWL, check));
	file = get_arg(check);
	free(check);
	*arg += i + j;
	return (file);
}

static int	open_file(char *file, int flag)
{
	int	fd;

	fd = 1;
	if (flag == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (flag == 2)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		print_erro_int(strerror(errno));
	return (fd);
}

static int	get_fd(t_cmd *cmd, char *output, int flag)
{
	char	*file;
	char	*temp;

	temp = output;
	while (*temp)
	{
		if (*temp == '>' && !check_inside(output, temp))
		{
			file = get_outfile(&temp, output);
			if (!file)
				return (0);
			if (cmd->fd_out != 1)
			{
				close (cmd->fd_out);
				cmd->fd_out = 1;
			}
			cmd->fd_out = open_file(file, flag);
			free(file);
			continue ;
		}
		temp++;
	}
	return (1);
}

int	get_fdout(t_cmd *cmd, int flag, char *output)
{
	if (flag > 2)
	{
		print_error_syntax(flag, '>');
		return (0);
	}
	return (get_fd(cmd, output, flag));
}
