# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: evocatur <evocatur@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/23 15:15:17 by user              #+#    #+#              #
#    Updated: 2023/08/09 11:28:51 by evocatur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCS = $(MAIN_SRC) $(LIBFT)

LIBFT  = libft/*.c

MAIN_SRC = pipex.c pipex_utils.c

OBJ = *.o

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

bexe: all
	@echo "     - Executing $(NAME)..."
	@./$(NAME) deepthought "grep Now" "grep Deep" "wc -w" outfile


vleaks:all
	@valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) deepthought "grep Now" "grep Deep" outfile
	@echo "     "
	@echo "     "

xleaks:all
	@leaks --atExit -- ./$(NAME) infile "ls -l" "grep rw" outfile

norm:
	@norminette $(SRC)

clean: 
	@${RM} ${OBJ}

fclean: clean
	@${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re