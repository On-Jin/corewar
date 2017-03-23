# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/02 18:45:43 by ntoniolo          #+#    #+#              #
#    Updated: 2017/02/28 13:28:48 by ntoniolo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FLAGS = -Wall -Werror -Wextra

SRC = basic/ft_memset.c basic/ft_bzero.c basic/ft_memcpy.c basic/ft_memccpy.c basic/ft_memmove.c basic/ft_memchr.c basic/ft_memcmp.c basic/ft_strlen.c basic/ft_strdup.c basic/ft_strcpy.c basic/ft_strcat.c basic/ft_strncat.c basic/ft_strlcat.c basic/ft_strchr.c basic/ft_strrchr.c basic/ft_strstr.c basic/ft_strnstr.c basic/ft_strcmp.c basic/ft_strncmp.c basic/ft_atoi.c basic/ft_isalpha.c basic/ft_isdigit.c basic/ft_isalnum.c basic/ft_isascii.c basic/ft_isprint.c basic/ft_toupper.c basic/ft_tolower.c basic/ft_memalloc.c basic/ft_memdel.c basic/ft_strnew.c basic/ft_strdel.c basic/ft_strclr.c basic/ft_striter.c basic/ft_striteri.c basic/ft_strmap.c basic/ft_strmapi.c basic/ft_strequ.c basic/ft_strnequ.c basic/ft_strsub.c basic/ft_strjoin.c basic/ft_strtrim.c basic/ft_strsplit.c basic/ft_itoa.c basic/ft_putchar.c basic/ft_putstr.c basic/ft_putendl.c basic/ft_putnbr.c basic/ft_putchar_fd.c basic/ft_putstr_fd.c basic/ft_putendl_fd.c basic/ft_putnbr_fd.c basic/ft_lstnew.c basic/ft_lstdelone.c basic/ft_lstdel.c basic/ft_lstadd.c basic/ft_lstiter.c basic/ft_lstmap.c basic/ft_strncpy.c basic/ft_atoi_base.c basic/ft_itoa_base.c basic/get_next_line.c basic/ft_abs.c\
	srcs/ft_printf.c \
	srcs/check.c \
	srcs/write_other.c \
	srcs/write_width.c \
	srcs/dipfoux.c \
	srcs/sc_c.c \
	srcs/sc_s.c \
	srcs/preci.c \
	srcs/arg_dipfoux.c \
	srcs/write_f.c \
	srcs/ft_putbuffer.c \
	printf_fun/ft_multitoa_base.c printf_fun/ft_putwchar.c printf_fun/ft_putwstr.c printf_fun/ft_sizebit.c printf_fun/ft_wcharlen.c printf_fun/ft_putnbrbase.c printf_fun/ft_wctoc.c printf_fun/ft_watoa.c printf_fun/ft_wstrlen.c printf_fun/ft_wstrnew.c printf_fun/ft_wstrsub.c printf_fun/ft_strjoinfree.c printf_fun/ft_isin.c printf_fun/ft_dotoa.c \
	basic/ft_realloc.c \
	basic/ft_lstinsert.c

OBJET = $(SRC:.c=.o)

.PHONY: all, clean, fclean, re, $(NAME)

all: start $(NAME) end

$(NAME): $(OBJET)
	@ar rc $(NAME) $(OBJET) && ranlib $(NAME)

start :
	@echo "\033[4m\033[33mCreation de $(NAME)   ...\033[0m"

end :
	@echo "\033[4m\033[1m\033[32m>$(NAME) done.\033[0m"

%.o: %.c
	gcc $(FLAGS) -o $@ -c $^

clean:
	@echo "Delete .o"
	@/bin/rm -f $(OBJET)

fclean: clean
	@echo "Delete .o & .a"
	@/bin/rm -f $(NAME)

re: fclean all
