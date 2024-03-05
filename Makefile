# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/22 19:51:00 by ggiertzu          #+#    #+#              #
#    Updated: 2024/03/05 16:53:19 by irivero-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS  := -g -O0 -Wall -Werror -Wextra
CC		:= gcc
LIBFT_D	:= ./libft
LIBFT_L	:= libftprintf.a
LIBFT	:= $(LIBFT_D)/$(LIBFT_L)


HEADERS	:= -I include -I $(LIBFT_D) -I .
SRCS	:= parser.c src/tokenizer/*.c
OBJS	:= ${SRCS:.c=.o}
NAME	:= minishell

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
