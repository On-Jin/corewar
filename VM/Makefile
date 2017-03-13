# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gnebie <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/06 05:41:35 by gnebie            #+#    #+#              #
#    Updated: 2017/03/13 12:56:10 by ntoniolo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY : clean, fclean, re, all $(NAME)
.SUFFIXES :

CC = gcc
FLAGS = -Wall -Werror -Wextra -g
##############################-g
SPE_FLAGS =
DEBUG_FLAG = -fsanitize=address

NAME = corewar

LIB = $(LIB_DIR)libft.a
LIB_DIR = ./../includes/libft/

SRC2 = vm_champ_number_to_position.c \
		vm_champ_position_to_number.c \
		vm_op_0_create.c \
		vm_op_0_exec.c \
		vm_op_10_create.c \
		vm_op_10_exec.c \
		vm_op_11_create.c \
		vm_op_11_exec.c \
		vm_op_12_create.c \
		vm_op_12_exec.c \
		vm_op_13_create.c \
		vm_op_13_exec.c \
		vm_op_14_create.c \
		vm_op_14_exec.c \
		vm_op_15_create.c \
		vm_op_15_exec.c \
		vm_op_16_create.c \
		vm_op_16_exec.c \
		vm_op_1_create.c \
		vm_op_1_exec.c \
		vm_op_2_create.c \
		vm_op_2_exec.c \
		vm_op_3_create.c \
		vm_op_3_exec.c \
		vm_op_4_create.c \
		vm_op_4_exec.c \
		vm_op_5_create.c \
		vm_op_5_exec.c \
		vm_op_6_create.c \
		vm_op_6_exec.c \
		vm_op_7_create.c \
		vm_op_7_exec.c \
		vm_op_8_create.c \
		vm_op_8_exec.c \
		vm_op_9_create.c \
		vm_op_9_exec.c \
		vm_recup_all_process.c \
		vm_recup_arena_num.c \
		vm_recup_indirect_num.c \
		vm_recup_process_reg.c \
		vm_verif_i_code.c \

SRC = VM_main.c \
		vm_copy_process.c \
		vm_create_flags.c \
		vm_create_process.c \
		vm_destroy_process.c \
		vm_do_cycles.c \
		vm_champ_process.c \
		vm_init_champ.c \
		vm_init_process.c \
		vm_innit_to_0.c \
		vm_ocp_tools.c \
		vm_show_arene.c \
		vm_verif_macro.c \
		ft_void_error.c \
		ft_int_error.c \
		ft_itoa_base_unsigned.c \
		ncurses_end.c \
		ncurses_key.c \
		ncurses_init.c

SRC_DIR = ./srcs/
SRC2_DIR = ./srcs/vm_op_mod/

OBJ = $(SRC:.c=.o)
OBJ2 = $(SRC2:.c=.o)
OBJ_DIR = ./objs/
OBJ2_DIR = ./objs/vm_op_mod/

INC = ../includes/

all : $(NAME)

$(NAME) : $(LIB) $(OBJ_DIR) $(OBJ2_DIR) $(addprefix $(OBJ_DIR), $(OBJ)) $(addprefix $(OBJ_DIR), $(OBJ2)) ../includes/corewar.h
	$(CC) $(FLAGS) $(SPE_FLAGS) $(addprefix $(OBJ_DIR), $(OBJ)) $(addprefix $(OBJ_DIR), $(OBJ2)) $(LIB) -I$(INC) -o $(NAME) -lncurses

boubou :
	-lncurses

$(LIB) :
	@(cd $(LIB_DIR) && MAKE)

$(OBJ_DIR) :
	mkdir $(OBJ_DIR)

$(OBJ2_DIR) :
	mkdir $(OBJ2_DIR)

$(OBJ_DIR)%.o : $(addprefix $(SRC_DIR), %.c)
	$(CC) $(FLAGS) $(SPE_FLAGS) -I$(INC) -c $(addprefix $(SRC_DIR), $(SRC))
	mv $(OBJ) $(OBJ_DIR)

$(OBJ_DIR)%.o : $(addprefix $(SRC2_DIR), %.c)
	$(CC) $(FLAGS) $(SPE_FLAGS) -I$(INC) -c $(addprefix $(SRC2_DIR), $(SRC2))
	mv $(OBJ2) $(OBJ_DIR)

clean :
	rm -f $(addprefix $(OBJ_DIR), $(OBJ)) $(addprefix $(OBJ_DIR), $(OBJ2))
	@(cd $(LIB_DIR) && MAKE $@)

fclean : clean
	rm -f $(NAME)
	@(cd $(LIB_DIR) && MAKE $@)

re : fclean all
