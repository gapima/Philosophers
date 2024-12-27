NAME = philo

CC = cc
CFLAGS = -g3 -Wall -Wextra -Werror -fsanitize=thread
RM = rm -f

INC = ./include

HEADERS = -I $(INC)

FILES = src/main.c src/routine.c src/output.c src/exit.c src/utils0.c src/utils1.c
OBJS = $(FILES:%.c=%.o)

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(CFLAGS) $(HEADERS) -o $(NAME)
	@echo "SUCCESS!!"

clean:
	@$(RM) $(OBJS)
	@echo "Objects cleaned!"

fclean: clean
	@$(RM) $(NAME)
	@echo "Executable cleaned!"

re: fclean all

.PHONY: all clean fclean re
