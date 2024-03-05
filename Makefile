# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/22 19:51:00 by ggiertzu          #+#    #+#              #
#    Updated: 2024/03/05 17:38:40 by ggiertzu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS  := -g -O0 -Wall -Werror -Wextra
CC		:= gcc
LIBFT_D	:= ./libft
LIBFT_L	:= libftprintf.a
LIBFT	:= $(LIBFT_D)/$(LIBFT_L)
LIBS	:=	-lreadline -lhistory libftprintf.a


HEADERS	:= -I include -I $(LIBFT_D) -I .
SRCS	:= parser.c src/tokenizer/token_line.c src/tokenizer/token_append.c	\
src/tokenizer/token_list.c src/tokenizer/token_utils.c \
src/tokenizer/tokenizer.c src/main.c
OBJS	:= ${SRCS:.c=.o}
NAME	:= minishell

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_D)
	cp $(LIBFT) .
clean:
	rm -rf $(OBJS)
	make clean -C $(LIBFT_D)
fclean: clean
	rm -rf $(NAME)
	make fclean -C $(LIBFT_D)
re: clean all

.PHONY: all, clean, fclean, re, libmlx
