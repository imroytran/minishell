#include "../includes/minishell.h"

void	del_argv(void *argv)
{
	t_cmd	*t_cmd;

	t_cmd = argv;
	free_split(t_cmd->cmd);
}

int	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (0);
}
