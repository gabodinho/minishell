NAME = minishell

LIBFT = libft.a
LIBFT_DIR = libft
LIBFT_PATH = $(LIBFT_DIR)/libft.a

CC = cc 
CFLAGS = -Wall -Wextra -Werror
RLFLAGS = -lreadline

SRC = $(shell find src -type f -name "*.c")
LIB = minishell.h
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(LIBFT_PATH):
	make bonus -C $(LIBFT_DIR)
	mv $(LIBFT_DIR)/libft.a .

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(RLFLAGS) -o $@ $^

%.o: %.c $(LIB)
	$(CC) $(CFLAGS) -c -o $@ $<
clean:
	rm -f $(OBJ)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)

re: fclean all

.PHONY: all clean fclean re