# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/22 19:51:00 by ggiertzu          #+#    #+#              #
#    Updated: 2024/04/19 15:36:36 by irivero-         ###   ########.fr        #
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
SRCS := \
	src/builtins/builtins_utils.c \
	src/builtins/cd.c \
	src/builtins/cd_helpers.c \
	src/builtins/echo.c \
	src/builtins/env.c \
	src/builtins/exit.c \
	src/builtins/export.c \
	src/builtins/export_helpers_0.c \
	src/builtins/export_helpers_1.c \
	src/builtins/pwd.c \
	src/builtins/unset.c \
	src/execution/exec_exec.c \
	src/execution/exec_heredoc.c \
	src/execution/exec_pipe.c \
	src/execution/exec_redir.c \
	src/execution/exec_tree.c \
	src/execution/exec_utils.c \
	src/execution/exec_builtins.c \
	src/main.c \
	src/start_shell.c \
	src/environment.c \
	src/signals/signals.c \
	src/signals/signals_main.c \
	src/clear_shell.c \
	src/expander/expand.c \
	src/expander/expand_extension.c \
	src/expander/expand_helper_0.c \
	src/expander/expand_quotes.c \
	src/expander/pre_expand.c \
	src/tokenizer/get_input.c \
	src/tokenizer/token_append.c \
	src/tokenizer/token_line.c \
	src/tokenizer/token_list.c \
	src/tokenizer/token_quotes.c \
	src/tokenizer/token_utils.c \
	src/tokenizer/tokenizer.c \
	src/parser/parse_exe.c \
	src/parser/parse_pipe.c \
	src/parser/parse_redir.c \
	src/parser/parse_utils.c \
	src/parser/prepare_heredoc.c \
	src/get_data.c

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
