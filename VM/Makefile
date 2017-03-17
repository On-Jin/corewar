# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/13 14:54:46 by ntoniolo          #+#    #+#              #
#    Updated: 2017/03/17 18:43:38 by ntoniolo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY : clean, fclean, re, all $(NAME)
.SUFFIXES :

CC = gcc
FLAGS = -Wall -Werror -Wextra -fsanitize=address
SPE_FLAGS =  -lncurses -g
OPTI_FLAGS = -O2
DEBUG_FLAG = -fsanitize=address
EXTRA_FLAGS =
E = -O2 -Wchar-subscripts -Wcomment -Wformat=2 -Wimplicit-int \
	-Werror-implicit-function-declaration -Wmain -Wparentheses \
	-Wsign-compare -Waggregate-return -Wstrict-prototypes \
	-Wmissing-prototypes -Wmissing-declarations -Wmissing-noreturn \
	-Wformat -Wmissing-format-attribute -Wno-deprecated-declarations \
	-Wpacked -Wredundant-decls -Wnested-externs -Winline -Wlong-long \
	-Wunreachable-code \
	-Wsequence-point -Wreturn-type -Wswitch -Wtrigraphs -Wunused \
	-Wuninitialized -Wunknown-pragmas -Wfloat-equal -Wundef \
	-Wshadow -Wpointer-arith -Wbad-function-cast \
	-Wpadded  -Wwrite-strings -Wconversion
	#-Weverything -std=c89 -pedantic -MMD

NAME = corewar

LIB = $(LIB_DIR)libft.a
LIB_DIR = ./../includes/libft/

SRC3 = ncurses_end.c \
	   ncurses_key.c \
	   ncurses_kirby.c \
	   ncurses_cycle.c \
	   ncurses_show_arene.c \
	   ncurses_init.c

SRC2 = vm_champ_number_to_position.c \
	   vm_champ_position_to_number.c \
	   vm_add_valid.c \
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
	   vm_verif_datas.c \
	   vm_op_jump.c \
	   vm_put_nbr_in_arene.c

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
	  vm_verif_macro.c \
	  vm_start_op_code.c \
	  ft_void_error.c \
	  ft_int_error.c \
	  ft_square_root.c \
	  ft_gcd.c \
	  ft_itoa_base_unsigned.c

SRC_DIR = ./srcs/
SRC2_DIR = ./srcs/vm_op_mod/
SRC3_DIR = ./srcs/ncurses/

OBJ = $(SRC:.c=.o)
OBJ2 = $(SRC2:.c=.o)
OBJ3 = $(SRC3:.c=.o)

OBJ_DIR = ./objs/
OBJ2_DIR = ./objs/vm_op_mod/
OBJ2_DIR = ./objs/ncurses/

INC = ../includes/

all : $(NAME)

$(NAME) : $(LIB) $(OBJ_DIR) $(OBJ2_DIR) $(OBJ3_DIR) $(addprefix $(OBJ_DIR), $(OBJ)) $(addprefix $(OBJ_DIR), $(OBJ2)) $(addprefix $(OBJ_DIR), $(OBJ3)) ../includes/corewar.h
	@($(CC) $(FLAGS) $(SPE_FLAGS) $(addprefix $(OBJ_DIR), $(OBJ)) $(addprefix $(OBJ_DIR), $(OBJ2)) $(addprefix $(OBJ_DIR), $(OBJ3)) $(LIB) -I$(INC) -o $(NAME))
	@(echo "\033[2K\033[2F")
	@(echo "\n\033[5m Ouverture de l'arene de Combat !!!!!!!!!!!\033[0m")

boubou :
	@(echo "bonjour");
	@(echo "bonjour")
	@(echo "\033[2F")
	@(echo "bonjour");

$(LIB) :
	@(cd $(LIB_DIR) && MAKE)

$(OBJ_DIR) :
	mkdir $(OBJ_DIR)

$(OBJ2_DIR) :
	mkdir $(OBJ2_DIR)

$(OBJ3_DIR) :
	mkdir $(OBJ3_DIR)

$(OBJ_DIR)%.o : $(addprefix $(SRC_DIR), %.c)
	@(echo "\033[35m Preparation du terrin \033[31m\t\c")
	@(echo "{\t$@\t}")
	@($(CC) $(FLAGS) -I$(INC) -c -o $@ $< $(EXTRA_FLAGS))
	@(echo "\033[2F")

$(OBJ_DIR)%.o : $(addprefix $(SRC2_DIR), %.c)
	@(echo "\033[33m Preparation des armes \033[31m\t\c")
	@(echo "{\t$@\t}")
	@($(CC) $(FLAGS) -I$(INC) -c -o $@ $< $(EXTRA_FLAGS))
	@(echo "\033[2F")

$(OBJ_DIR)%.o : $(addprefix $(SRC3_DIR), %.c)
	@(echo "\033[93m Demarage de la retransmition video \033[31m\t\c")
	@(echo "{\t$@\t}")
	@($(CC) $(FLAGS) -I$(INC) -c -o $@ $< $(EXTRA_FLAGS))
	@(echo "\033[2F")

clean :
	@(rm -f $(addprefix $(OBJ_DIR), $(OBJ)) $(addprefix $(OBJ_DIR), $(OBJ2)) $(addprefix $(OBJ_DIR), $(OBJ3)))
	@(echo "\033[32m Destruction des infrastructures De l'arène\033[0m")
	@(cd $(LIB_DIR) && MAKE $@)

fclean : clean
	@(rm -f $(NAME))
	@(echo "\033[32m Destruction de l'arène de combat\033[0m")
	@(cd $(LIB_DIR) && MAKE $@)

re : fclean all
