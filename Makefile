# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: evocatur <evocatur@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/23 15:15:17 by user              #+#    #+#              #
#    Updated: 2023/06/19 13:20:20 by evocatur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCS = $(MAIN_SRC) $(LIBFT)

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
	@./$(NAME) infile "ls -l" "grep 2022" outfile
	@echo "     - Done -"

exe1: all
	@echo "     - Executing $(NAME)..."
	@./$(NAME) deepthought "grep Now" "wc -w" outfile
	@echo "     - Done -"

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