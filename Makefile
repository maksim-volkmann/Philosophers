# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/09 10:52:21 by mvolkman          #+#    #+#              #
#    Updated: 2024/05/22 17:02:37 by mvolkman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc -pthread
# CFLAGS =
CFLAGS = -Wall -Wextra -Werror -g
# -fsanitize=thread

SRC = \
	actions.c \
	argument_validator.c \
	create_dinner.c \
	getters_setters.c \
	init_items.c \
	init_values.c \
	philo.c \
	range_validator.c \
	routines.c \
	threads.c \
	time_management.c \
	utils.c \
	cleanup.c \

OBJ = $(SRC:.c=.o)

INCLUDES = -I./include

NAME = philo

GREEN = \033[0;32m
BLUE = \033[0;34m
ORANGE = \033[38;5;214m
RED = \033[0;31m
YELLOW = \033[0;33m
WHITE = \033[0;37m

# Rules
all: $(NAME)
	@echo "$(GREEN)$(NAME) compiled successfully!$(WHITE)"

$(NAME): $(OBJ)
	@echo "$(BLUE)Building $(NAME)$(WHITE)"
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(INCLUDES)
	@echo "$(GREEN)$(NAME) created successfully!$(WHITE)"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)
	@echo "$(GREEN)Compiled $< successfully!$(WHITE)"

clean:
	@echo "$(RED)Cleaning object files...$(WHITE)"
	rm -f $(OBJ)

fclean: clean
	@echo "$(RED)Cleaning binaries...$(WHITE)"
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
