# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cobecque <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/09 15:33:03 by cobecque          #+#    #+#              #
#    Updated: 2018/03/09 16:53:37 by cobecque         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY:all clean fclean re

NAME = corewar

INC_NAME = ./../includes
LIBP_NAME = libftprintf.a
LIB_NAME = libft.a
SRC_NAME = main.c	champs.c	vm.c	op.c	ocp.c	arena.c\
		   magic.c	option.c	instruction/add.c\
		   instruction/reg_write.c \
		   instruction/live.c \
		   instruction/sti.c\
		   instruction/ld.c\
		   instruction/zjmp.c\
		   instruction/fork.c\
		   instruction/xor.c \
		   instruction/lfork.c \
		   instruction/aff.c \
		   instruction/and.c \
		   instruction/or.c \
		   instruction/ldi.c \
		   instruction/lld.c \
		   instruction/lldi.c \
		   instruction/sub.c \
		   instruction/st.c \
		   instruction/get_relative.c \
		   instruction/catch_reg_val.c \
		   instruction/dup_pros.c \
		   verbose.c \
		   octet.c \
		   add_process.c \
		   message.c \
		   process.c \
		   murder.c \
		   cycle.c \
		   adv.c \
		   process2.c \
		   process3.c \
		   ncurses.c \
		   init_nc.c \
		   spec_nc.c \
		   music.c \
		   tool_file.c

LIB_DIR = ../libft
LIBP_DIR = ../libft/src/printf
SRC_DIR = ./src
OBJ_DIR = ./obj_vm

LIB_PATH = $(addprefix $(LIB_DIR)/,$(LIB_NAME))
LIBP_PATH = $(addprefix $(LIBP_DIR)/,$(LIBP_NAME))
SRC_PATH = $(addprefix $(SRC_DIR)/,$(SRC_NAME))
OBJ_PATH = $(addprefix $(OBJ_DIR)/,$(SRC_NAME:.c=.o))

CC = gcc
FLAGS = -Wall -Werror -Wextra -fsanitize=address

all :
	@clear
	@printf $(CN_MAG) "=== ->  Compil all libs  <- ==="
	@make -C $(LIBP_DIR)
	@printf "\n"
	@printf $(CN_YEL) "=== ->  Compil corewar  <- ==="
	@mkdir -p obj_vm
	@mkdir -p obj_vm/instruction
	@$(MAKE) $(NAME)

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c ./../includes/core.h
	@$(CC) $(FLAGS) -I $(INC_NAME) -o $@ -c $<
	@printf $(C_BLU) "        [ ✔ ] $<"

$(NAME): $(OBJ_PATH)
	@$(CC) $(FLAGS) $(OBJ_PATH) $(LIB_PATH) $(LIBP_PATH) -o $(NAME) -lncurses
	@printf $(C_CYA) "        [ ✔ ] compiled → $(NAME)"
	@printf "\n"
	@mv $(NAME) ../

clean :
	@printf "\n"
	@printf $(CN_YEL) "================= COREWAR ================="
	@make clean -C $(LIBP_DIR)
	@/bin/rm -f $(OBJ_PATH)
	@rm -rf ./obj_vm
	@printf $(C_RED) " [ ✔ ] deleted objects path"
	@printf "\n"

fclean : clean
	@printf "\n"
	@rm -f $(LIBP_PATH)
	@rm -f $(LIB_PATH)
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
