# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: evocatur <evocatur@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/23 15:15:17 by user              #+#    #+#              #
#    Updated: 2023/07/26 16:10:58 by evocatur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCS = $(MAIN_SRC) $(LIBFT)

SRCS_BONUS = pipex_bonus_utils.c pipex.bonus.c

LIBFT  = libft/*.c

MAIN_SRC = *.c

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
bonus:

empty: all
	@echo "     - Executing $(NAME)..."
	@./$(NAME)
	@echo "     - Done -"

leaks:all
	@leaks --atExit -- ./$(NAME) infile "ls -l" "wc -l" outfile
	@echo "     "
	@echo "     "
	@leaks --atExit -- ./$(NAME)

clean: 
	@${RM} ${OBJ}

fclean: clean
	@${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re