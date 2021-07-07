CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = libftprintf.a

SRCS = ft_printf_util1.c ft_printf_util2.c ft_printf_util3.c \
		ft_printf.c print.c print_get.c print_number.c parse.c

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	ar rc $@ $^

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean : $(OBJS)
	rm -f $(OBJS)

fclean : $(OBJS) $(NAME)
	rm -f $^

bonus : $(OBJS)
	ar rc $(NAME) $^

re : fclean
	make all

.PHONY : all clean fclean re
