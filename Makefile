# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cobecque <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/10 18:52:38 by cobecque          #+#    #+#              #
#    Updated: 2017/11/07 16:37:21 by cobecque         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY:all clean fclean re

NAME = asm

INC_NAME = ./inc
LIBP_NAME = libftprintf.a
LIB_NAME = libft.a
SRC_NAME = main.c	op.c	struct.c	encodage.c	function_supp.c\
		   function_ocp.c	function_param.c	function_spec.c\
		   function_label.c	fill_file.c	function_binair.c

LIB_DIR = ./libft
LIBP_DIR = ./libft/src/printf
SRC_DIR = ./src
OBJ_DIR = ./mdr

LIB_PATH = $(addprefix $(LIB_DIR)/,$(LIB_NAME))
LIBP_PATH = $(addprefix $(LIBP_DIR)/,$(LIBP_NAME))
SRC_PATH = $(addprefix $(SRC_DIR)/,$(SRC_NAME))
OBJ_PATH = $(addprefix $(OBJ_DIR)/,$(SRC_NAME:.c=.o))

CC = gcc
FLAGS = -Wall -Werror -Wextra -fsanitize=address -g3

all :
	@printf $(CN_MAG) "=== ->  Compil all libs  <- ==="
	@make -C $(LIBP_DIR)
	@printf "\n"
	@printf $(CN_YEL) "=== ->  Compil corewar  <- ==="
	@mkdir -p mdr
	@$(MAKE) $(NAME)

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c
	@$(CC) $(FLAGS) -I $(INC_NAME) -o $@ -c $<
	@printf $(C_BLU) "        [ ✔ ] $<"

$(NAME): $(OBJ_PATH)
	@$(CC) $(FLAGS) $(OBJ_PATH) $(LIB_PATH) $(LIBP_PATH) -o $(NAME)
	@printf $(C_CYA) "        [ ✔ ] compiled → $(NAME)"
	@printf "\n"

clean :
	@printf "\n"
	@make clean -C $(LIBP_DIR)
	@/bin/rm -f $(OBJ_PATH)
	@rm -rf ./mdr
	@printf $(C_RED) " [ ✔ ] deleted objects path"
	@printf "\n"

fclean : clean
	@printf "\n"
	@rm -f $(LIBP_PATH)
	@/bin/rm -f $(NAME)
	@printf $(C_RED) " [ ✔ ] deleted binary file → $(NAME)"
	@printf "\n"

re: fclean all

# color
C_RED = "\e[31;m%s\e[0m\n"
C_GRN = "\e[32;m%s\e[0m\n"
C_YEL = "\e[33;m%s\e[0m\n"
C_BLU = "\e[34;m%s\e[0m\n"
C_MAG = "\e[35;m%s\e[0m\n"
C_CYA = "\e[36;m%s\e[0m\n"

# color + \n

CN_RED = "\e[31;m%s\e[0m\n\n"
CN_GRN = "\e[32;m%s\e[0m\n\n"
CN_YEL = "\e[33;m%s\e[0m\n\n"
CN_BLU = "\e[34;m%s\e[0m\n\n"
CN_MAG = "\e[35;m%s\e[0m\n\n"
CN_CYA = "\e[36;m%s\e[0m\n\n"
