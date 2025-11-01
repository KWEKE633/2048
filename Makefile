# Linux ver

NAME = 2048

LIBFT_DIR = pkg
LIBFT_A = $(LIBFT_DIR)/libft.a

SRC_DIR = cmd

SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/utils.c $(SRC_DIR)/color.c

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude -I$(LIBFT_DIR)
LDFLAGS = -L$(LIBFT_DIR) -lft -lncurses

all: $(LIBFT_A) $(NAME)

$(NAME): $(OBJS) $(LIBFT_A)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

$(LIBFT_A):
	@make -C $(LIBFT_DIR)

clean:
	@make clean -C $(LIBFT_DIR)
	rm -f $(OBJS)

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	rm -f $(NAME) bestscore.txt

re: fclean all

.PHONY: all clean fclean re



# Mac ver

# NAME = 2048

# LIBFT_DIR = pkg
# LIBFT_A = $(LIBFT_DIR)/libft.a

# SRC_DIR = cmd

# SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/utils.c $(SRC_DIR)/color.c

# OBJS = $(SRCS:.c=.o)

# CC = cc
# CFLAGS = -Wall -Wextra -Werror -Iinclude -I$(LIBFT_DIR) -I/opt/homebrew/opt/ncurses/include
# LDFLAGS = -L$(LIBFT_DIR) -lft -L/opt/homebrew/opt/ncurses/lib -lncurses

# all: $(LIBFT_A) $(NAME)

# $(NAME): $(OBJS) $(LIBFT_A)
# 	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

# $(LIBFT_A):
# 	@make -C $(LIBFT_DIR)

# clean:
# 	@make clean -C $(LIBFT_DIR)
# 	rm -f $(OBJS)

# fclean: clean
# 	@make fclean -C $(LIBFT_DIR)
# 	rm -f $(NAME) bestscore.txt

# re: fclean all

# .PHONY: all clean fclean re
