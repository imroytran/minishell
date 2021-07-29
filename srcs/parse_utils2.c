#include "../includes/minishell.h"

char	**free_argv(char **argv, int argc, char *err)
{
	if (err)
		printf("%s\n", err);
	while (argc--)
		free(argv[argc]);
	free(argv);
	return (NULL);
}

static int	get_newarg2(char *pars, char **arg, int i)
{
	char	*temp;

	temp = ft_substr(pars, 0, i);
	if (!temp)
		return (print_erro_int("ERROR: Malloc"));
	*arg = get_arg(temp);
	free(temp);
	if (*arg == NULL)
		return (1);
	else
		return (2);
}

static int	add_path(char **arg, int argc)
{
	if (argc == 1 && !check_builtins(arg[0]))
	{
		if (!check_path(&arg[0]))
		{
			free(arg[0]);
			free(arg);
			return (0);
		}
	}
	return (1);
}

int	get_newarg(char **temp, char **line, int *argc)
{
	char	*pars;
	int		i;
	int		j;

	pars = *line;
	i = 0;
	while (pars[i] != '\0' && (!ft_strchr("<> \t", pars[i])
			|| (ft_strchr("<> \t", pars[i]) && check_inside(pars, pars + i))))
		i++;
	j = get_newarg2(pars, &temp[*argc], i);
	if (!j)
		return (0);
	else if (j == 1)
		return (i);
	*argc += 1;
	if (!add_path(temp, *argc))
		return (0);
	return (i);
}
