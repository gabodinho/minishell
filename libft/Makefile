# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ggiertzu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/20 18:33:58 by ggiertzu          #+#    #+#              #
#    Updated: 2023/11/24 17:35:45 by ggiertzu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
CC = cc
CFLAGS = -Werror -Wall -Wextra -I. -Ilibft
MAKE = make bonus -C
RM = rm -f

SRCS = print_dec.c  print_hex.c print_ptr.c printf_utils1.c \
printf_utils2.c printf_utils3.c print_str.c ft_printf.c
OBJS = $(SRCS:.c=.o)

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	cp $(LIBFT) .
	mv libft.a $(NAME)
	ar crs $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) $(LIBFT_DIR)

bonus: $(NAME)
clean:
	${RM} $(OBJS)
	make clean -C $(LIBFT_DIR)
fclean: clean
	$(RM) $(NAME)
	make fclean -C $(LIBFT_DIR)
re: fclean all

.PHONY: all clean fclean re bonus
