NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror #-fsanitize=thread -g3

SRCS = ft_atoi.c ft_malloc.c ft_strlen.c get_time.c init_data.c initialize_philosopher.c \
		join_and_destroy.c philo.c philosopher_actions.c print_error.c print_message.c 

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re