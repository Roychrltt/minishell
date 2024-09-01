# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/07 12:18:43 by xiaxu             #+#    #+#              #
#    Updated: 2024/09/01 12:17:52 by xiaxu            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc 

CFLAGS = -Wall -Wextra -Werror -O2

SRC_DIR = ./src/
	  
SRC_FILES = main.c \
			signals.c \
			builtins/builtins.c \
			builtins/export.c \
			builtins/unset.c \
			builtins/echo.c \
			builtins/env.c \
			builtins/pwd.c \
			parsing/check_quotes.c \
			parsing/check_metas.c \
			parsing/check_metas_utils.c \
			parsing/tokenize.c \
			parsing/token_utils.c \
			parsing/tokens_to_list.c \
			execute/execute.c \
			execute/deal_quotes.c \
			execute/pipex_utils1.c

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))

#INC = -Iincludes/ -Ilibft 

INC = -Iincludes/ -Ilibft -I/opt/homebrew/include

#LDFLAGS = -Llibft -lft -lreadline

LDFLAGS = -Llibft -lft -L/opt/homebrew/lib -lreadline

OBJ = $(SRC:.c=.o)

LIBFT_LIB = ./libft/libft.a

LIBFT = ./libft/

RM = rm -rf

all: $(NAME)

$(NAME): $(LIBFT_LIB) $(OBJ)
	if [ ! -f $(NAME) ] || [ `find $(OBJ) -newer $(NAME) | wc -l` -ne 0 ]; then \
	$(CC) $(CFLAGS) $(INC) $(OBJ) -o $(NAME) $(LDFLAGS); \
		printf "$(ERASE)$(GREEN)Program$(RESET) $(CYAN)$(BOLD)$(NAME)$(RESET) $(GREEN)created!\n$(RESET)"; \
	else \
		printf "$(ERASE)$(YELLOW)No relink needed for$(RESET) $(CYAN)$(BOLD)$(NAME)\n$(RESET)"; \
	fi \

$(LIBFT_LIB):
	$(MAKE) -sC libft

%.o: %.c 
	${CC} $(CFLAGS) $(INC) -c $< -o $@
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
