CC = cc
FLAGS = -Wall -Wextra -Werror

NAME =  minishell
PRINTF = utils/ft_printf/printf.a

SRCS =  main.c \
		dup_env.c \
		ft_garbage.c \
		builtins/ft_cd.c \
		builtins/ft_echo.c \
		builtins/ft_env.c \
		builtins/ft_exit.c \
		builtins/ft_export.c \
		builtins/ft_pwd.c \
		builtins/ft_unset.c \
		execution/execution.c \
		execution/check_per.c \
		execution/redirection_out.c \
		utils/ft_atoi.c \
		utils/ft_split.c \
		utils/ft_strchr.c \
		utils/ft_strcmp.c \
		utils/ft_strdup.c \
		utils/ft_strdup_gc.c \
		utils/ft_strjoin.c \
		utils/ft_strlen.c \
		utils/ft_strncmp.c \
		utils/ft_strtok.c \
		utils/ft_substr.c \
		utils/ft_strncpy.c \
		utils/ft_memcpy.c \
		utils/ft_memset.c \
		utils/ft_bzero.c \
		utils/ft_calloc.c \
		utils/ft_realloc.c \
		utils/ft_isalpha.c \
		utils/ft_isdigit.c \
		utils/ft_isalnum.c


OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	make -C utils/ft_printf
	$(CC) $(CFLAGS) $(OBJS) $(PRINTF) -lreadline -o $(NAME)

clean:
	make -C utils/ft_printf clean
	rm -f $(OBJS)

fclean: clean
	make -C utils/ft_printf fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
