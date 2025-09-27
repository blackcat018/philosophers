NAME = philo
LIBNAME = libmini.a
CC = gcc
# LDFLAGS = -lreadline -lncurses
CFLAGS = -Wall -Wextra -Werror -g

# Main files
files = mandatory/actions/actions mandatory/actions/fork_manager \
		mandatory/actions/time_and_printing mandatory/initialization/init \
		mandatory/philos/philos mandatory/main mandatory/parsing/parsing \

CFILES = $(files:%=%.c)
OBJS = $(files:%=%.o)

LIBFT_DIR = mandatory/utils/libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBFT) $(LDFLAGS)

$(LIBNAME): $(OBJS)
	ar crs $@ $(OBJS)

%.o: %.c mandatory/philo.h
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME) $(LIBNAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re