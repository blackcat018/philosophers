# Executables
NAME = philo
BONUS_NAME = philo_bonus

# Compiler flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
#LDFLAGS = -lreadline -lncurses

# Mandatory source files
M_FILES = mandatory/actions/actions.c \
          mandatory/actions/fork_manager.c \
          mandatory/actions/time_and_printing.c \
          mandatory/initialization/init.c \
          mandatory/philos/philos.c \
          mandatory/main.c \
          mandatory/parsing/parsing.c

M_OBJS = $(M_FILES:.c=.o)

# Bonus source files
B_FILES = Bonus/actions_bonus.c \
          Bonus/init_bonus.c \
          Bonus/main_bonus.c \
          Bonus/parsing_bonus.c \
          Bonus/philos_bonus.c

B_OBJS = $(B_FILES:.c=.o)

# Libft
LIBFT_DIR = mandatory/utils/libft
LIBFT = $(LIBFT_DIR)/libft.a

# Default target: mandatory
all: $(NAME)

# Mandatory executable
$(NAME): $(M_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $(M_OBJS) $(LIBFT) $(LDFLAGS)

# Bonus executable
bonus: $(B_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(BONUS_NAME) $(B_OBJS) $(LIBFT) $(LDFLAGS)

# Compile object files
%.o: %.c mandatory/philo.h
	$(CC) $(CFLAGS) -c $< -o $@

# Libft
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Clean object files
clean:
	rm -f $(M_OBJS) $(B_OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

# Full clean (executables + object files)
fclean: clean
	rm -f $(NAME) $(BONUS_NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

# Rebuild everything
re: fclean all

.PHONY: all bonus clean fclean re
