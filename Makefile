NAME = libftprintf.a

CC = cc
CFLAGS = -Wall -Wextra 

SRCS = ft_printf.c ft_putchar_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_strchr.c ft_strlen.c print_hexa.c print_char.c print_int.c print_string.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re