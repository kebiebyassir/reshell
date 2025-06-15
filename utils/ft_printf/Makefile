NAME = printf.a

SRC = ft_printf.c \
      ft_putchar.c \
      ft_puthex.c \
      ft_putnbr.c \
      ft_putunbr.c \
      ft_putptr.c \
      ft_putstr.c

OBJ = $(SRC:.c=.o)

CC = cc

FLGS = -Wall -Wextra -Werror

RM = rm -f

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all

%.o: %.c
	$(CC) $(FLGS) -c $< -o $@

.PHONY : all clean fclean re
