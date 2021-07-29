#include "../includes/minishell.h"

char	*make_path(char *cmd)
{
	char	*temp;
	char	*path;

	if (cmd[0] != '~')
		path = ft_strdup(cmd);
	else
	{
		temp = ft_substr(cmd, 1, ft_strlen(cmd) - 1);
		if (!temp)
			do_exit(1);
		path = ft_strjoin(get_value_from_list(find_env("HOME")), temp);
		free(temp);
	}
	if (!path)
		do_exit(1);
	return (path);
}

void	change_direct(char *cmd)
{
	char	*temp;

	temp = make_path(cmd);
	g_mini.global_output = chdir(temp);
	free(temp);
}

int	do_cd(char **cmd)
{
	char	*temp;
	char	cwd[PATH_MAX];

	temp = ft_strjoin("OLDPWD=", getcwd(cwd, sizeof(cwd)));
	if (temp == NULL)
		do_exit(1);
	add_env(temp);
	free (temp);
	if (cmd[1] != NULL)
		change_direct(cmd[1]);
	else
		g_mini.global_output = chdir(get_value_from_list(find_env("HOME")));
	if (g_mini.global_output == -1)
	{
		printf("minishell: cd: %s: No such file or directory\n", cmd[1]);
		g_mini.global_output = 1;
		return (g_mini.global_output);
	}
	else
		temp = ft_strjoin("PWD=", getcwd(cwd, sizeof(cwd)));
	if (temp == NULL)
		do_exit(1);
	add_env(temp);
	free (temp);
	return (g_mini.global_output);
}

int	do_pwd(void)
{
	int		ret;
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_putstr_fd(cwd, 1);
		ft_putchar_fd('\n', 1);
		ret = 0;
	}
	else
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putchar_fd('\n', 2);
		ret = -1;
	}
	return (ret);
}
