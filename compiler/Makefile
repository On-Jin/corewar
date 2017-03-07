# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gnebie <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/06 05:39:15 by gnebie            #+#    #+#              #
#    Updated: 2017/03/06 05:39:17 by gnebie           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#A faire : deplacer le compiler.c dans un docier srcs
#ou changer le nom du dossier SRC_DIR = ./srcs/

.PHONY : clean, fclean, re, all $(NAME)
.SUFFIXES :

CC = gcc
FLAGS = -Wall -Werror -Wextra
SPE_FLAGS =
DEBUG_FLAG = -fsanitize=address

NAME = asm

LIB = $(LIB_DIR)libft.a
LIB_DIR = ./../includes/libft/

SRC =
SRC_DIR = ./srcs/

OBJ = $(SRC:.c=.o)
OBJ_DIR = ./objs/

INC = ./includes/

all : $(NAME)

$(NAME) : $(LIB) $(OBJ_DIR) $(addprefix $(OBJ_DIR), $(OBJ)) ../includes/corewar.h
	$(CC) $(FLAGS) $(SPE_FLAGS) $(addprefix $(OBJ_DIR), $(OBJ)) $(LIB) -I$(INC) -o $(NAME)

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
