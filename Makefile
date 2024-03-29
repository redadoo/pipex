# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/23 15:15:17 by user              #+#    #+#              #
#    Updated: 2023/10/23 14:42:35 by edoardo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCS = $(MAIN_SRC) $(LIBFT)

SRCS_BONUS = $(BONUS_SRC) $(LIBFT)

LIBFT  = libft/*.c

MAIN_SRC = src/pipex.c src/pipex_utils.c src/pipex_utils_1.c

BONUS_SRC = src_bonus/pipex_bonus.c src_bonus/pipex_bonus_utils.c src/pipex_utils_1.c

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
	@${CC} -c $(FLAGS) $(SRCS) src_bonus/pipex_bonus_utils.c

exe: all
	@echo "     - Executing $(NAME)..."
	@./$(NAME) infile "ls -l" "grep rw" outfile
	@echo "     - Done -"

exe1: all
	@echo "     - Executing $(NAME)..."
	@./$(NAME) infile "grep majesty" "wc -w" outfile
	@echo "     - Done -"
bonus_exe: bonus
	@echo "     - Executing $(NAME)..."
	@./$(NAME) infile "grep majesty" "wc -w" "wc -l" "ls -l" "grep rome" "wc -l" outfile
	@echo "     - Done -"
	
bonus:
	@echo "     - Making object files..." 
	@${CC} -c $(FLAGS) $(SRCS_BONUS)
	@echo "     - Compiling $(NAME) bonus..." 
	@${CC} $(FLAGS) $(OBJ) -o $(NAME)
	@echo "- Compiled -"
	@${RM} $(OBJ)

leaks: all
	@valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) deepthought "luca" "wc " outfile 

bonus_leaks: bonus
	@valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) infile "grasdasasdep majesty" "wc -w" "wc -l" "ls -l" "grep rome" "wc -l" outfile 1 1 1 1

norm:
	@norminette $(MAIN_SRC) $(SRCS_BONUS) pipex.h

clean: 
	@${RM} ${OBJ}

fclean: clean
	@${RM} ${NAME}

re: fclean all

re_bonus: fclean bonus

.PHONY: all clean fclean re