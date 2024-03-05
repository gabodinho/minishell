# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ggiertzu <ggiertzu@student.42berlin.d      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/22 19:51:00 by ggiertzu          #+#    #+#              #
#    Updated: 2024/03/03 18:31:56 by ggiertzu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS  := -g -O0 -Wall -Werror -Wextra
CC		:= gcc
LIBFT_D	:= ./libft
LIBFT_L	:= libftprintf.a
LIBFT	:= $(LIBFT_D)/$(LIBFT_L)


HEADERS	:= -I include -I $(LIBFT_D) -I .
SRCS	:= parser.c
OBJS	:= ${SRCS:.c=.o}
NAME	:= parser

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(LIBFT) $(LIBMLX) $(OBJS)
	$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_D)
clean:
	rm -rf $(OBJS)
	make clean -C $(LIBFT_D)
fclean: clean
	rm -rf $(NAME)
	make fclean -C $(LIBFT_D)
re: clean all

.PHONY: all, clean, fclean, re, libmlx
