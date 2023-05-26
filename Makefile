# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: evocatur <evocatur@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/23 15:15:17 by user              #+#    #+#              #
#    Updated: 2023/05/26 16:18:43 by evocatur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCS = $(LIBFT_SRC) $(MAIN_SRC)


LIBFT_SRC = ft_libft/*.c

MAIN_SRC = *.c

OBJ = *.o

CC = gcc
CFLAGS = -Wall -Wextra -Werror

RM = rm -rf

all: $(NAME)

$(NAME): $(OBJ)
	@echo $(CURSIVE) $(GRAY) "     - Compiling $(NAME)..." $(NONE)
	@${CC} $(FLAGS) $(OBJ) -o $(NAME)
	@echo $(GREEN)"- Compiled -"$(NONE)
	@${RM} $(OBJ)
	
$(OBJ): $(SRCS)
	@echo $(CURSIVE)$(GRAY) "     - Making object files..." $(NONE)
	@${CC} -c $(SRCS)

exe: all
	@echo "     - Executing $(NAME)..."
	@./$(NAME) infile "ls -l" "wc -l" outfile
	@echo "\n     - Done -"

clean: 
	@${RM} ${OBJ}

fclean: clean
	@${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re