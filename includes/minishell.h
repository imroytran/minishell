#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <term.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/types.h>
# include <stdio.h>
# include "../libft/libft.h"
# include <errno.h>
# include <sys/wait.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>

# define PROMT	"minishell: "
# define ERR_UNCL_QT "minishell: unexpected EOF while looking for matching `\"\'"
# define ERR_TOKEN_PIPE	"minishell: syntax error near unexpected token `|\'"
# define ERR_TOKEN_NEWL "minishel: syntax error near unexpected token `newline\'"
# define ERR_SUCH_FD	"minishel: no such file or directory:"

# define PATH_MAX 4098

typedef struct s_minishell
{
	t_list	*env_list;
	int		global_output;
	int		is_fork;
	int		start_pid;
}	t_minishell;

t_minishell	g_mini;

typedef struct s_cmd
{
	char	**cmd;
	int		fd_input;
	int		fd_out;
	int		fdpipe[2];
}	t_cmd;

typedef struct s_var_env
{
	char	*name;
	char	*value;
}				t_var_env;

int			get_parse(t_list **commands, char *line);
int			redirect(char *line, t_cmd *cmd);
int			check_inside(char *temp, const char *redir);
int			check_builtins(char *command);
int			check_builtins_pipe(char *command);
char		**ft_split_outside(char *str, char c);
int			init_env_list(char *env[]);
int			do_unset(char *argv[]);
char		**lst_to_char(void);
int			do_env(char **cmd);
int			is_bad_var_name(char *name);
int			do_export(char *argv[]);
void		free_content(void *content);
int			do_exit(int error_nb);
void		sort_env_list(void);
void		print_export_list(void);
t_var_env	*make_content(char *env);
void		export_unset_error(char *name, char *command);
t_list		*find_env(char *name);
void		get_value(t_var_env *content, char *env, int i);
char		*get_value_from_list(t_list *env);
void		get_name(t_var_env *content, char *env, int i);
char		*ft_getenv(char *name);
void		*print_erro(char *err, char *to_free);
int			print_erro_int(char *err);
void		*print_error_syntax(int flag, char c);
int			move_arr(char **arr, char **temp, int *count);
int			get_newarg(char **temp, char **line, int *argc);
int			check_path(char **arg);
int			exec(t_list *commands);
int			check_builtins_not_pipe(char *command);
int			get_fdin(t_cmd *cmd, int flag_out, char *input);
int			get_fdout(t_cmd *cmd, int flag, char *output);

void		add_env(char *env);
int			add_char(char **str, char c);
char		*get_arg(char *arg);
int			do_echo(char **argv);
int			do_cd(char **cmd);
int			do_pwd(void);
void		rl_replace_line(const char *str, int i);
void		del_argv(void *argv);
int			free_split(char **split);
int			check_closed_quotes(const char *arg);
void		our_sig_proc(int sig);
int			ft_strcmp(const char *s1, const char *s2);
void		increment_sh_lvl(void);
int			exit_buildin(char **argv);

#endif
