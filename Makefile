# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cobecque <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/09 15:33:03 by cobecque          #+#    #+#              #
#    Updated: 2018/03/09 16:12:08 by cobecque         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY:all corewar asm clean fclean re

CORE_PATH = ./vm
CORE_NAME = ./corewar

ASM_PATH = ./assembleur
ASM_NAME = ./asm

all:
	clear
	@printf "\n"
	@printf "\n"
	@printf "\n"
	@printf "\n"
	@printf "\n"
	@printf "\n"
	@printf "\n"
	@printf "\n"
	@printf "\n"
	@printf "\n"
	@printf "\n"
	@printf "\n"
	@printf "\n"
	@printf "\n"
	@printf "\n"
	@printf "\n"
	@printf "\n"
	@printf "\n"
	@printf "\n"
	@printf "\n"
	@printf "\n"
	@printf "\n"
	@printf "\n"
	@printf "\n"
	@printf "\n"
	@printf "\n"
	@printf "\n"
	@printf "\n"
	@printf "\n"
	@printf "\n"
	@printf "\n"
	@printf "\n"
	@printf $(CN_RED) "                         Makefile usage :                                                                     "
	@printf "\n"
	@printf $(CN_BLU) "                             -make corewar to compil corewar                                                  "
	@printf "\n"
	@printf $(CN_YEL) "                             -make asm to compil asm                                                          "
	@printf "\n"
	@printf "\n"
	@printf "\n"
	@printf "\n"
	@printf "\n"
	@printf "\n"
	@printf "\n"
	@printf "\n"
	@printf "\n"
	@printf "\n"
	@printf "\n"
	@printf "\n"
	@printf "\n"
	@printf "\n"
	@printf "\n"
	@printf "\n"
	@printf "\n"
	@printf "\n"
	@printf "\n"
	@printf "\n"
	@printf "\n"
	@printf "\n"
	@printf "\n"
	@printf "\n"
	@printf "\n"
	@printf "\n"
	@printf "\n"
	@printf "\n"
	@printf "\n"

corewar:
	@make -C $(CORE_PATH)

asm:
	@make -C $(ASM_PATH)

clean:
	@clear
	@make clean -C $(CORE_PATH)
	@make clean -C $(ASM_PATH)

fclean:
	@make fclean -C $(CORE_PATH)
	@make fclean -C $(ASM_PATH)
	@rm -rf $(CORE_NAME)
	@rm -rf $(ASM_NAME)

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
