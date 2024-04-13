# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/23 15:15:17 by user              #+#    #+#              #
#    Updated: 2024/04/13 17:24:36 by edoardo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			= pipex

CC			  	= gcc 
FLAGS		  	= -Wall -Wextra -Werror 
RM			  	= rm -rf

OBJDIR        	= .objFiles


MAIN_SRC		= src/pipex src/pipex_utils src/pipex_utils_1
BONUS_SRC		= src_bonus/pipex_bonus src_bonus/pipex_bonus_utils src/pipex_utils_1

FILES			= $(MAIN_SRC)
FILES_BONUS		= $(BONUS_SRC)

SRC			  	= $(FILES:=.c)
OBJ			  	= $(addprefix $(OBJDIR)/, $(FILES:=.o))
BONUS_OBJ		= $(addprefix $(OBJDIR)/, $(FILES_BONUS:=.o))
HEADER		  	= pipex.h

NONE			="\033[0m"
GREEN			="\033[32m"
GRAY			="\033[2;37m"
CURSIVE			="\033[3m"
YELLOW			="\033[1;33"


LINKS = -Llibft/ -lft

.PHONY: all clean fclean re leaks

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	@echo $(CURSIVE) $(GRAY) "     - Compiling libft library ..." $(NONE)
	@cd libft/  && make > /dev/null 2>&1 && make clean > /dev/null 2>&1
	@echo $(CURSIVE)$(GRAY) "      - Making object files..." $(NONE)
	@echo $(CURSIVE) $(GRAY) "     - Compiling $(NAME)..." $(NONE)
	@$(CC)  $(FLAGS) $(OBJ) $(LINKS) -o $(NAME)
	@echo $(GREEN)"- Compiled -"$(NONE)

$(OBJDIR)/%.o: %.c $(HEADER)
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) -c $< -o $@

bonus: $(BONUS_OBJ) $(HEADER)
	@echo $(CURSIVE) $(GRAY) "     - Compiling libft library ..." $(NONE)
	@cd libft/  && make > /dev/null 2>&1 && make clean > /dev/null 2>&1
	@echo $(CURSIVE)$(GRAY) "      - Making object files..." $(NONE)
	@echo $(CURSIVE) $(GRAY) "     - Compiling $(NAME)..." $(NONE)
	@$(CC)  $(FLAGS) $(BONUS_OBJ) $(LINKS) -o $(NAME)
	@echo $(GREEN)"- Compiled -"$(NONE)

$(OBJDIR)/%.o: %.c $(HEADER)
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) -c $< -o $@
	
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
	

leaks: all
	@valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) deepthought "luca" "wc " outfile 

bonus_leaks: bonus
	@valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) infile "grasdasasdep majesty" "wc -w" "wc -l" "ls -l" "grep rome" "wc -l" outfile 1 1 1 1

norm:
	@norminette $(MAIN_SRC) $(SRCS_BONUS) pipex.h

clean:
	@$(RM) $(OBJDIR) $(OBJ)
	@$(RM) leaks.txt

fclean: clean
	@${RM} ${NAME}

re: fclean all

re_bonus: fclean bonus
