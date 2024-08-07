# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/07 12:18:43 by xiaxu             #+#    #+#              #
#    Updated: 2024/08/07 12:19:33 by xiaxu            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = main.c
	  
OBJ = ${SRC:.c=.o}

CC = cc -Wall -Wextra -Werror

all: ${NAME}

$(NAME): ${OBJ} minishell.h
	ar rc ${NAME} ${OBJ}
	printf "$(ERASE)$(CYAN)$(BOLD)$@$(RESET) $(GREEN)created!\n$(RESET)"

%.o: %.c minishell.h
	${CC} -I. -c $< -o $@
	printf "$(ERASE)$(BLUE) > Compilation: $(RESET) $<"

clean:
	printf "$(ERASE)$(GREEN)Cleaning up...$(RESET)"
	rm -rf ${OBJ} ${OBJ_BONUS}
	printf "$(ERASE)$(GREEN)Clean finished!\n$(RESET)"

fclean: clean
	printf "$(GREEN)Fcleaning up...$(RESET)"
	rm -rf ${NAME}
	printf "$(ERASE)$(GREEN)Fclean finished!\n$(RESET)"

re: fclean all

.PHONY: all clean fclean re 
.SILENT:

# COLORS
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
MAGENTA = \033[35m
CYAN = \033[36m
BOLD = \033[1m
ERASE = \033[2K\r
RESET = \033[0m
