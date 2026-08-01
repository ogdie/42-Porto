NAME = push_swap

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -Iincludes

SRC_DIR = src
SRCS = \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/utils.c \
	$(SRC_DIR)/utils_checks.c \
	$(SRC_DIR)/stack.c \
	$(SRC_DIR)/stack_normalize.c \
	$(SRC_DIR)/parse.c \
	$(SRC_DIR)/parse_flags.c \
	$(SRC_DIR)/operations_swap.c \
	$(SRC_DIR)/operations_push.c \
	$(SRC_DIR)/operations_rotate.c \
	$(SRC_DIR)/operations_reverse.c \
	$(SRC_DIR)/disorder.c \
	$(SRC_DIR)/sort_small.c \
	$(SRC_DIR)/sort_simple.c \
	$(SRC_DIR)/sort_simple_utils.c \
	$(SRC_DIR)/sort_simple_utils2.c \
	$(SRC_DIR)/sort_medium.c \
	$(SRC_DIR)/sort_complex.c \
	$(SRC_DIR)/sort_adaptive.c \
	$(SRC_DIR)/bench.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c includes/push_swap.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
