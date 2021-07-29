
NAME		=	minishell

SRCS		=	./srcs/main.c \
				./srcs/buildin.c \
				./srcs/echo.c \
				./srcs/ft_split_outside.c \
				./srcs/parse.c \
				./srcs/do_env.c \
				./srcs/do_exit.c \
				./srcs/do_export.c \
				./srcs/do_unset.c \
				./srcs/env_parse.c \
				./srcs/exec.c \
				./srcs/export_utils.c \
				./srcs/export_utils2.c \
				./srcs/export_utils3.c \
				./srcs/get_path.c \
				./srcs/get_redir_input.c \
				./srcs/get_redir_output.c \
				./srcs/free_cmds.c \
				./srcs/redirection.c \
				./srcs/parse_utils.c \
				./srcs/parse_utils2.c

LIBFT		=	libft

LIBS		= 	./libft/libft.a

OBJS		=	$(SRCS:.c=.o)

HEADER		= 	./includes/minishell.h

%.o:		%.c $(HEADER)
			$(CC)   -c $< -o $(<:.c=.o) $(CFLAGS)


CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror 

FLAGS		=	-lreadline -ltermcap -g -L/Users/$(USER)/.brew/Cellar/readline/8.1/lib/ -I/Users/$(USER)/.brew/Cellar/readline/8.1/include

RM			=	rm -f

all :		$(NAME)

$(NAME) :	$(OBJS) $(LIBFT)
			$(MAKE) -C $(LIBFT) bonus
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -I$(HEADER) $(LIBS) $(FLAGS) 
			@echo "minishell is ready"

$(LIBFT) :  libft/*.c libft/*.h
			$(MAKE) -C $(LIBFT) bonus
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -I$(HEADER) $(LIBS) $(FLAGS)


clean :		
			$(MAKE) -C $(LIBFT) clean
			$(RM) $(OBJS)

fclean 	:	clean
			$(MAKE) -C $(LIBFT) fclean
			$(RM) $(NAME)

re :		fclean all

.PHONY :	all clean fclean re