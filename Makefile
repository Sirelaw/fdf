# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/16 20:23:06 by oipadeol          #+#    #+#              #
#    Updated: 2022/01/04 12:49:38 by oipadeol         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	fdf

CC = gcc

SRC =	main.c input_handling_2.c get_next_line/get_next_line.c input_handling.c\
		utils_fdf.c matrix_op.c ft_strtol.c

# FLAGS = -Wall -Werror -Wextra

FLAGS = 

SUB_DIR = libft

INC_LIB = libft.a

BONUS = 

B_SRC = 

SUB_DIR_M = 

all: $(NAME)

# %.o: %.c
# 	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@
	

$(NAME): $(OBJ) $(SRC)
	@$(CC) $(OBJ) $(SRC) $(SUB_DIR)/$(INC_LIB) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)
	@echo "mini_libx compiled!"

clean:
	@rm -f $(NAME)
	@echo "fdf deleted"

fclean: clean

re: fclean all