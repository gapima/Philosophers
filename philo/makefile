

NAME = philo

CC = cc
CFLAGS = -g3 -Wall -Wextra -Werror -lpthread
RM = rm -f

INC = ./include
LIBFT = ./libft

HEADERS = -I $(INC)
LIBS = ./libft/libft.a

FILES = src/main.c src/routine.c src/output.c src/exit.c
OBJS = $(FILES:%.c=%.o)

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) $(HEADERS)	-c $< -o $@

$(NAME): $(OBJS)
	@make -C $(LIBFT)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)
	@echo "SUCCESS!!"

clean:
	@rm -rf $(OBJS)
	@make clean -C libft

fclean: clean
	@make fclean -C libft
	@rm -rf
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re