# Executable
NAME = philo

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

# Source files
SRC = actions/actions.c \
      actions/fork_manager.c \
      actions/time_and_printing.c \
      initialization/init.c \
      philos/philos.c \
      parsing/parsing.c \
      utils/ft_atoi.c \
      utils/ft_isdigit.c \
      utils/ft_putnbr_fd.c \
      utils/ft_putstr_fd.c \
      main.c

OBJ = $(SRC:.c=.o)

# Default target
all: $(NAME)

# Link executable
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Compile object files
%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	rm -f $(OBJ)

# Full clean
fclean: clean
	rm -f $(NAME)

# Rebuild
re: fclean all

.PHONY: all clean fclean re
