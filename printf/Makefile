# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile2                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rostroh <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/10 15:59:34 by rostroh           #+#    #+#              #
#    Updated: 2017/02/11 12:30:49 by rostroh          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

HEAD = ft_printf.h

SRC = conv.c \
	  space.c \
	  print.c \
	  params.c \
	  gestion.c \
	  get_base.c \
	  ft_printf.c \
	  condition.c \
	  ft_putwchar.c \
	  gestion_print.c \
	  wchar_fonction.c \
	  shitty_fonction.c \
	  binary_to_decimal.c \
	  more_shitty_fonction.c \
	  libft/ft_atoi.c \
	  libft/ft_isspace.c \
	  libft/ft_isdigit.c \
	  libft/ft_long_itoa.c \
	  libft/ft_putchar.c \
	  libft/ft_putstr.c \
	  libft/ft_strcmp.c \
	  libft/ft_strcpy.c \
	  libft/ft_strjoin.c \
	  libft/ft_strlen.c \
	  libft/ft_strnew.c \
	  libft/ft_strrev.c \
	  libft/ft_strsub.c

OBJ = conv.o \
	  space.o \
	  print.o \
	  params.o \
	  gestion.o \
	  get_base.o \
	  ft_printf.o \
	  condition.o \
	  ft_putwchar.o \
	  gestion_print.o \
	  wchar_fonction.o \
	  shitty_fonction.o \
	  binary_to_decimal.o \
	  more_shitty_fonction.o \
	  ft_atoi.o \
	  ft_isspace.o \
	  ft_isdigit.o \
	  ft_long_itoa.o \
	  ft_putchar.o \
	  ft_putstr.o \
	  ft_strcmp.o \
	  ft_strcpy.o \
	  ft_strjoin.o \
	  ft_strlen.o \
	  ft_strnew.o \
	  ft_strrev.o \
	  ft_strsub.o

all: $(NAME)

$(NAME):
	gcc -Wall -Werror -Wextra -c $(SRC) -I $(HEAD)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

gg:
	gcc $(SRC) main.c -I $(HEAD) -L. -lft

clean:
	make clean -C libft
	rm -rf $(OBJ)

fclean: clean
	make fclean -C libft
	rm -rf $(NAME)
	rm -rf libft.a

re: fclean all
