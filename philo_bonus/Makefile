# Executable
NAME = philo_bonus

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

# Source files
SRC = actions_bonus.c \
      init_bonus.c \
      main_bonus.c \
      parsing_bonus.c \
      philos_bonus.c \
      utils_bonus/ft_atoi_bonus.c \
      utils_bonus/ft_isdigit_bonus.c \
      utils_bonus/ft_putnbr_fd_bonus.c \
      utils_bonus/ft_putstr_fd_bonus.c

OBJ = $(SRC:.c=.o)

# Default target
all: $(NAME)

# Link executable
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Compile object files
%.o: %.c philo_bonus.h
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
