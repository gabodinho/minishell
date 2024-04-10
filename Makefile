# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: irivero- <irivero-@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/22 19:51:00 by ggiertzu          #+#    #+#              #
#    Updated: 2024/04/10 10:13:50 by irivero-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS  := -g -O0 -Wall -Werror -Wextra
CC		:= cc
LIBFT_D	:= ./libft
LIBFT_L	:= libftprintf.a
LIBFT	:= $(LIBFT_D)/$(LIBFT_L)
LIBS	:=	-lreadline $(LIBFT) #-lhistory
ifeq ($(shell uname),Linux)
    LIBS += -lhistory
endif

HEADERS	:= -I $(LIBFT_D)/libft -I include -I $(LIBFT_D) -I .
SRCS	:= parser.c src/tokenizer/token_line.c src/tokenizer/token_append.c	\
src/tokenizer/token_list.c src/tokenizer/token_utils.c  \
src/tokenizer/tokenizer.c src/main.c syntax_check.c environment.c src/expand.c\
search_exec.c src/exec_builtins.c src/builtins/echo.c src/builtins/exit.c \
src/builtins/pwd.c src/builtins/builtins_utils.c src/builtins/cd.c \
src/builtins/unset.c src/builtins/export.c src/signals.c \
src/builtins/export_helpers.c exit_status.c src/builtins/env.c \
src/builtins/cd_helpers.c src/tokenizer/token_quotes.c \
src/tokenizer/get_input.c pre_expand.c expand_extension.c exec_nodes.c \
src/clear_shell.c

OBJS	:= ${SRCS:.c=.o}
NAME	:= minishell

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(LIBFT) $(OBJS)
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

.PHONY: all, clean, fclean, re
