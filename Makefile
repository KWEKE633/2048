# Linux ver

NAME = 2048
DNAME := $(NAME)_debug

LIBFT_DIR = pkg
LIBFT_A = $(LIBFT_DIR)/libft.a

SRC_DIR = cmd

SRCS = 
SRCS += $(SRC_DIR)/main.c
SRCS += $(SRC_DIR)/utils.c
SRCS += $(SRC_DIR)/presentation.c
SRCS += $(SRC_DIR)/color.c

OBJS = $(SRCS:.c=.o)
DOBJS := $(SRCS:.c=_d.o)
DEP = $(OBJS:.o=.d)
DDEP = $(DOBJS:.o=.d)

CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -MP -Iinclude -I$(LIBFT_DIR)
LFLAGS = -L$(LIBFT_DIR) -lft -lncurses
DFLAGS := -fdiagnostics-color=always -g3 -fsanitize=address

.PHONY: all
all: $(LIBFT_A) $(NAME)

$(NAME): $(OBJS) $(LIBFT_A)
	$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) -o $@

.PHONY: debug
debug: $(LIBFT_A) $(DNAME)

$(DNAME): $(DOBJS) $(LIBFT_A)
	$(CC) $(CFLAGS) $(DFLAGS) $(DOBJS) $(LFLAGS) -o $@

-include $(DEP)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

-include $(DDEP)
%_d.o: %.c
	$(CC) $(CFLAGS) $(DFLAGS) -c $< -o $@

$(LIBFT_A):
	@make -C $(LIBFT_DIR)

.PHONY: clean
clean:
	@make fclean -C $(LIBFT_DIR)
	rm -f $(OBJS) $(DOBJS) $(DEP) $(DDEP) $(DNAME)

.PHONY: fclean
fclean: clean
	@make fclean -C $(LIBFT_DIR)
	rm -f $(NAME) bestscore.txt

.PHONY: re
re: fclean all

# Mac ver

# NAME = 2048

# LIBFT_DIR = pkg
# LIBFT_A = $(LIBFT_DIR)/libft.a

# SRC_DIR = cmd

# SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/utils.c $(SRC_DIR)/color.c

# OBJS = $(SRCS:.c=.o)

# CC = cc
# CFLAGS = -Wall -Wextra -Werror -Iinclude -I$(LIBFT_DIR) -I/opt/homebrew/opt/ncurses/include
# LFLAGS = -L$(LIBFT_DIR) -lft -L/opt/homebrew/opt/ncurses/lib -lncurses

# all: $(LIBFT_A) $(NAME)

# $(NAME): $(OBJS) $(LIBFT_A)
# 	$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) -o $(NAME)

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
