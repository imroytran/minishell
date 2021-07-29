#include "../includes/minishell.h"

int	add_char(char **str, char c)
{
	char	*temp;
	size_t	i;

	if (!*str)
		i = 0;
	else
		i = ft_strlen(*str);
	temp = malloc(sizeof(char) * i + 2);
	if (!temp)
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putchar_fd('\n', 2);
		return (0);
	}
	if (*str)
	{
		ft_strlcpy(temp, *str, i + 1);
		free(*str);
	}
	temp[i] = c;
	temp[i + 1] = '\0';
	*str = temp;
	return (1);
}

static char	*check_env(char **arg)
{
	char	*temp;
	char	*env;
	size_t	i;

	temp = *arg;
	temp++;
	i = 0;
	while (temp[i] && temp[i] != ' ' && temp[i] != '\t'
		&& temp[i] != '\"' && temp[i] != '\'')
		i++;
	env = ft_substr(temp, 0, i);
	if (!env)
		return (print_erro("ERROR: Malloc", NULL));
	*arg += i;
	if (ft_strcmp(env, "?"))
	{
		temp = ft_getenv(env);
		free(env);
	}
	else
		temp = ft_itoa(g_mini.global_output);
	return (temp);
}

static char	*write_env(char **arg, char *result)
{
	char	*temp;
	char	*str;
	size_t	i;

	temp = check_env(arg);
	if (temp)
		temp = ft_strdup(temp);
	if (!temp)
		return (result);
	if (!result)
		return (temp);
	i = ft_strlen(temp) + ft_strlen(result);
	str = malloc(sizeof(char) * i + 1);
	if (!str)
		return (print_erro(strerror(errno), NULL));
	ft_memcpy(str, result, ft_strlen(result));
	ft_memcpy(str + ft_strlen(result), temp, ft_strlen(temp));
	str[i] = '\0';
	free(result);
	return (str);
}

char	*get_arg(char *arg)
{
	int		print;
	char	c;
	char	*temp;

	print = 0;
	c = 0;
	temp = NULL;
	while (*arg)
	{
		if (*arg == '\\' && print == 0)
			print = 1;
		else if ((*arg == '\'' || *arg == '\"') && print == 0)
		{
			c = *arg;
			print = 1;
		}
		else if (print == 1 && *arg == c)
			print = 0;
		else if (*arg == '$' && c != '\'')
			temp = write_env(&arg, temp);
		else
			add_char(&temp, *arg);
		arg++;
	}
	return (temp);
}
