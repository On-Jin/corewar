# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gnebie <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/06 05:41:35 by gnebie            #+#    #+#              #
#    Updated: 2017/03/10 14:41:33 by ntoniolo         ###   ########.fr        #
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

SRC = VM_main.c \
		vm_create_flags.c \
		vm_init_champ.c \
		vm_show_arene.c \
		vm_ocp_tools.c \
		vm_verif_macro.c \
		vm_op_1_4.c \
		ft_void_error.c \
		ft_int_error.c \
		ft_itoa_base_unsigned.c

SRC_DIR = ./srcs/

OBJ = $(SRC:.c=.o)
OBJ_DIR = ./objs/

INC = ../includes/

all : $(NAME)

$(NAME) : $(LIB) $(OBJ_DIR) $(addprefix $(OBJ_DIR), $(OBJ)) ../includes/corewar.h
	$(CC) $(FLAGS) $(SPE_FLAGS) $(addprefix $(OBJ_DIR), $(OBJ)) $(LIB) -I$(INC) -o $(NAME) -lncurses

$(LIB) :
	@(cd $(LIB_DIR) && MAKE)

$(OBJ_DIR) :
	mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o : $(addprefix $(SRC_DIR), %.c)
	$(CC) $(FLAGS) $(SPE_FLAGS) -I$(INC) -c $(addprefix $(SRC_DIR), $(SRC))
	mv $(OBJ) $(OBJ_DIR)

clean :
	rm -f $(addprefix $(OBJ_DIR), $(OBJ))
	@(cd $(LIB_DIR) && MAKE $@)

fclean : clean
	rm -f $(NAME)
	@(cd $(LIB_DIR) && MAKE $@)

re : fclean all
