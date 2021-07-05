CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = libftprintf.a

SRCS = ft_printf_util1.c ft_printf_util2.c ft_printf_util3.c \
		ft_printf.c mypf.c condition.c print_number.c parse.c

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

re : fclean
	make all

#확인용
# test : $(SRCS)
# 	$(CC) $(CFLAGS) $(SRCS)
.PHONY : all clean fclean re test
