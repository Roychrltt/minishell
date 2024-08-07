# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/07 12:18:43 by xiaxu             #+#    #+#              #
#    Updated: 2024/08/07 12:45:02 by xiaxu            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc -Wall -Wextra -Werror -O2

SRC_DIR = ./src/
	  
SRC_FILES = main.c

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))

INC = -Iincludes/ -Ilibft

OBJ = $(SRC:.c=.o)

LIBFT_LIB = ./libft/libft.a

LIBFT = ./libft/

RM = rm -rf

all: $(NAME)

$(NAME): $(LIBFT_LIB) $(OBJ)
	printf "$(ERASE)$(CYAN)$(BOLD)$@$(RESET) $(GREEN)creating...$(RESET)"
	$(CC) $(INC) $(SRC) -L$(LIBFT) -lft -o $(NAME)
	printf "$(ERASE)$(CYAN)$(BOLD)$@$(RESET) $(GREEN)created!\n$(RESET)"

$(LIBFT_LIB):
	$(MAKE) -sC libft

%.o: %.c 
	${CC} $(INC) -c $< -o $@
	printf "$(ERASE)$(BLUE) > Compilation: $(RESET) $<"

clean:
	printf "$(ERASE)$(GREEN)Cleaning up...$(RESET)"
	$(MAKE) -sC libft clean
	$(RM) ${OBJ}
	printf "$(ERASE)$(GREEN)Clean finished!$(RESET)"

fclean: clean
	printf "$(ERASE)$(GREEN)Fcleaning up...$(RESET)"
	$(RM) ${NAME}
	$(RM) ${LIBFT_LIB}
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
