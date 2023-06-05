# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: evocatur <evocatur@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/23 15:15:17 by user              #+#    #+#              #
#    Updated: 2023/06/05 16:24:42 by evocatur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCS = $(MAIN_SRC) $(LIBFT)

LIBFT  = ft_libft/*.c

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
	@./$(NAME) infile "ls -l" "wc -l" outfile
	@echo "     - Done -"

#leak: all
#	LEAKS_E := $(shell which leaks)
#	ifeq ($(LEAKS_E),leaks not found)
# 	$(error "No leaks in, consider doing apt-get install leaks")
# 	endif
#	@leaks --atExit -- ./$(NAME) infile "ls -l" "wc -l" outfile
#	@echo "     "
#	@echo "     "
#	@leaks --atExit -- ./$(NAME)

clean: 
	@${RM} ${OBJ}
	@make -C $(LIBF_DIR) clean

fclean: clean
	@${RM} ${NAME}
	@make -C $(LIBF_DIR) fclean

re: fclean all

.PHONY: all clean fclean re