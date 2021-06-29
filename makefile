# CC = gcc
# CFLAGS = -Wall -Wextra -Werror

# LIB_DIR = ./lib

# INC = -I./lib -I./header

# NAME = libftprintf.a

# SRC_DIR = ./src
# SRC_NAME = ft_printf.c
# SRCS =

# OBJ_DIR = ./obj
# OBJ

CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = libftprintf.a

SRCS = ft_printf_util1.c ft_printf_util2.c ft_printf_util3.c ft_printf_util4.c \
		ft_printf.c

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


.PHONY : all clean fclean re bonus