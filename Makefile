# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gnebie <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/06 05:33:14 by gnebie            #+#    #+#              #
#    Updated: 2017/03/06 05:33:16 by gnebie           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY : clean, fclean, re, all, $(ASM_NAME), $(COREWAR_NAME), fall
.SUFFIXES :

CC = gcc
FLAGS = -Wall -Werror -Wextra
SPE_FLAGS =

AUTOR = auteur

COREWAR_NAME = corewar
ASM_NAME = asm
NAME = $(ASM_NAME) $(COREWAR_NAME)

COREWAR_DIR = ./VM/
ASM_DIR = ./compiler/

LIB = $(LIB_DIR)libft.a
LIB_DIR = ./includes/libft/

SRC =
SRC_DIR = ./srcs/

OBJ = $(SRC:.c=.o)
OBJ_DIR = ./objs/

INC = ./includes/

all : $(AUTOR) $(NAME) $(LIB)
	@(cd $(ASM_DIR) && make $(ASM_NAME))
	@(cp $(ASM_DIR)$(ASM_NAME) ./)
	@(cd $(COREWAR_DIR) && make $(COREWAR_NAME))
	@(cp $(COREWAR_DIR)$(COREWAR_NAME) ./)

$(AUTOR) :
	echo "gnebie\nntoniolo\nmprevot" > auteur;

$(LIB) :
	@(cd $(LIB_DIR) && make)

%.o : %.c

$(COREWAR_NAME) : $(LIB)
	@(cd $(COREWAR_DIR) && make)
	@(cp $(COREWAR_DIR)$(COREWAR_NAME) ./)

$(ASM_NAME) : $(LIB)
	@(cd $(ASM_DIR) && make)
	@(cp $(ASM_DIR)$(ASM_NAME) ./)

clean :
	@(cd $(LIB_DIR) && make clean)
	@(cd $(ASM_DIR) && make clean)
	@(cd $(COREWAR_DIR) && make clean)

fclean :
	@(rm -f $(NAME))
	@(cd $(LIB_DIR) && make fclean)
	@(cd $(ASM_DIR) && make fclean)
	@(cd $(COREWAR_DIR) && make fclean)

re : fclean all
