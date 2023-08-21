# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: evocatur <evocatur@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/23 15:15:17 by user              #+#    #+#              #
#    Updated: 2023/08/21 13:23:08 by evocatur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

NAME_BONUS = pipex_bonus

SRCS = $(MAIN_SRC) $(LIBFT)

SRCS_BONUS = $(BONUS_SRC) $(LIBFT)

LIBFT  = libft/*.c

MAIN_SRC = src/pipex.c src/pipex_utils.c

BONUS_SRC = bonus/pipex_bonus.c bonus/pipex_bonus_utils.c

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
	@${CC} -c $(FLAGS) $(SRCS) bonus/pipex_bonus_utils.c

exe: all
	@echo "     - Executing $(NAME)..."
	@./$(NAME) infile "ls -l" "grep rw" outfile
	@echo "     - Done -"

exe1: all
	@echo "     - Executing $(NAME)..."
	@./$(NAME) deepthought "grep majesty" "wc -w" outfile
	@echo "     - Done -"
	
pipex_bonus:
	@echo "     - Making object files..." 
	@${CC} -c $(FLAGS) $(SRCS_BONUS)
	@echo "     - Compiling $(NAME) bonus..." 
	@${CC} $(FLAGS) $(OBJ) -o $(NAME)
	@echo "- Compiled -"
	@${RM} $(OBJ)

leaks: all
	@leaks --atExit -- ./$(NAME) deepthought "grep majesty" "wc -w" outfile

bonus_leaks: all
	@leaks --atExit -- ./$(NAME) deepthought "grep majesty" "wc -w" "wc -l" outfile

norm:
	@norminette $(MAIN_SRC) $(SRCS_BONUS) pipex.h

clean: 
	@${RM} ${OBJ}

fclean: clean
	@${RM} ${NAME}

re: fclean all

re_bonus: fclean pipex_bonus

.PHONY: all clean fclean re