SRC = ./src/check_death.c ./src/init_data.c ./src/init_pthread_destroy.c \
		./src/main.c ./src/philo_eat.c ./src/philo_life.c ./src/tools_1.c \
		./src/tools_2.c

CC = cc
CFLAG =-Wall -Wextra -Werror -g -I./include/

OBJ =$(SRC:.c=.o)

NAME = philo

GREEN = \033[32m
BLINK = \033[5m
RESET = \033[0m
ORANGE = \033[33m

%.o: %.c
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@echo "Linking $(NAME)..."
	@$(CC) $(CFLAGS) $^ -o $@ -lpthread
	@echo  "$(GREEN)$(BLINK)$(NAME) compiled successfully!$(RESET)"

all: $(NAME)

clean:
	@echo "Cleaning object files..."
	@rm -rf $(OBJ)
	@echo "$(ORANGE)$(BLINK)Objects file cleanned.$(RESET)"

fclean: clean
	@echo "Cleaning $(NAME)..."
	@rm -rf $(NAME)
	@echo "$(ORANGE)$(BLINK)$(NAME) program cleanned.$(RESET)"

re: fclean all

.PHONY: all clean fclean re