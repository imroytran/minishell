#include "../includes/minishell.h"

int	do_echo(char **argv)
{
	int		i;
	int		flag;

	i = 1;
	if (argv[i] != NULL)
		flag = ft_strcmp(argv[i], "-n");
	else
		flag = 1;
	if (!flag)
		i = 2;
	while (argv[i])
	{
		ft_putstr_fd(argv[i], 1);
		if (argv[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (flag)
		ft_putchar_fd('\n', 1);
	return (0);
}
