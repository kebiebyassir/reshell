CC = cc
FLAGS = -Wall -Wextra -Werror

NAME =  minishell
PRINTF = utils/ft_printf/printf.a

SRCS =  *.c \


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
