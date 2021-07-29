#include "../includes/minishell.h"

int	print_erro_int(char *err)
{
	ft_putstr_fd(err, 2);
	ft_putchar_fd('\n', 2);
	return (0);
}

int	get_flag(char *line, char c)
{
	char	*temp;
	int		flag;

	temp = line;
	flag = 0;
	while (*temp)
	{
		if (*temp == c && *(temp - 1) != c && !check_inside(line, temp))
			flag = 1;
		else if (*temp == c && *(temp - 1) == c && !check_inside(line, temp))
			flag++;
		if (*temp != c && flag > 2)
			return (flag);
		temp++;
	}
	return (flag);
}

void	*print_error_syntax(int flag, char c)
{
	(void)flag;
	ft_putstr_fd(PROMT, 2);
	ft_putstr_fd("syntax error near unexpected token `", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("\'\n", 2);
	return (NULL);
}

int	redirect(char *line, t_cmd *cmd)
{
	char	*temp;
	int		flag_out;

	temp = line;
	flag_out = get_flag(line, '>');
	cmd->fd_input = 0;
	cmd->fd_out = 1;
	while (*temp)
	{
		if ((*temp == '>' || *temp == '<') && !check_inside(line, temp))
		{
			if (!get_fdout(cmd, flag_out, temp))
				return (0);
			if (!get_fdin(cmd, flag_out, temp))
				return (0);
			break ;
		}
		temp++;
	}
	return (1);
}
