# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/23 15:15:17 by user              #+#    #+#              #
#    Updated: 2023/08/02 15:01:57 by edoardo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

BONUS_NAME = pipex_bonus

SRCS = $(MAIN_SRC) $(LIBFT)

SRCS_BONUS = pipex_bonus_utils.c pipex_bonus.c

LIBFT  = libft/*.c

MAIN_SRC = *.c

OBJ = *.o

BONUS_OBJ = *.o

CC = gcc

CFLAGS = -Wall -Wextra -Werror

RM = rm -rf

all: $(NAME)

$(NAME): $(OBJ)
	@echo "     - Compiling $(NAME)..." 
	@${CC} $(FLAGS) $(OBJ) -o $(NAME)
	@echo "- Compiled -"
	@${RM} $(OBJ)
	
$(OBJ): $(SRCS)
	@echo "     - Making object files..." 
	@${CC} -c $(SRCS)

exe: all
	@echo "     - Executing $(NAME)..."
	@./$(NAME) infile "ls -l" "grep rw" outfile
	@echo "     - Done -"

exe1: all
	@echo "     - Executing $(NAME)..."
	@./$(NAME) deepthought "grep majesty" "wc -w" outfile
	@echo "     - Done -"

empty: all
	@echo "     - Executing $(NAME)..."
	@./$(NAME)
	@echo "     - Done -"
	
bonus: 
	@echo "     - Compiling $(BONUS_NAME)..." 
	@${CC} $(FLAGS) $(SRCS_BONUS) $(LIBFT) -o $(BONUS_NAME)
	@echo "- Compiled -"

bexe: bonus
	@echo "     - Executing $(BONUS_NAME)..."
	@./$(BONUS_NAME) deepthought "grep Now" "grep Deep" "grep inquired" "wc -w"  outfile


leaks:bonus
	@valgrind --leak-check=full --show-leak-kinds=all ./$(BONUS_NAME) deepthought "grep Now" "grep Deep" "grep inquired" "wc -w"  outfile
	@echo "     "
	@echo "     "

clean: 
	@${RM} ${OBJ}

fclean: clean
	@${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re