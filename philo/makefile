

NAME = philo

CC = cc
CFLAGS = -g3 -Wall -Wextra -Werror -lpthread
RM = rm -f

INC = ./include

HEADERS = -I $(INC)

FILES = src/main.c src/routine.c src/output.c src/exit.c src/utils.c
OBJS = $(FILES:%.c=%.o)

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) $(HEADERS)	-c $< -o $@

$(NAME): $(OBJS)
	@make -C
	@$(CC) $(OBJS) $(HEADERS) -o $(NAME)
	@echo "SUCCESS!!"

clean:
	@rm -rf $(OBJS)
	@make clean -C

fclean: clean
	@make fclean -C
	@rm -rf
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re