# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/16 20:23:06 by oipadeol          #+#    #+#              #
#    Updated: 2022/01/06 05:29:45 by oipadeol         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	fdf

CC =	gcc

SRC =	main.c get_next_line/get_next_line.c\
		input_handling/input_handling.c input_handling/input_handling_2.c\
		utils/rot_matrix.c utils/plotline.c utils/small_utils.c\
		utils/node_utils.c utils/mlx_utils.c utils/rotate_image.c\
		utils/graphical_utils.c utils/free_utils.c\

OBJ_F = obj_files

OBJ =	obj_files/main.o obj_files/free_utils.o obj_files/get_next_line.o\
		obj_files/graphical_utils.o obj_files/input_handling_2.o\
		obj_files/input_handling.o obj_files/mlx_utils.o \
		obj_files/plotline.o obj_files/rot_matrix.o obj_files/rotate_image.o\
		obj_files/small_utils.o obj_files/node_utils.o\

FLAGS = -Wall -Werror -Wextra

SUB_DIR = libft

INC_LIB = libft.a

all: $(NAME)

objects: $(SRC)
	@gcc -c $(FLAGS) $(SRC)
	@mv *.o $(OBJ_F)

$(NAME): $(SRC) $(SUB_DIR_M) $(SUB_DIR)/*.c
	@$(MAKE) -s objects
	@cd $(SUB_DIR) && $(MAKE) -s
	@$(CC) $(FLAGS) $(OBJ) $(SUB_DIR)/$(INC_LIB) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)
	@echo "fdf compiled!"

clean:
	@rm -f $(OBJ_F)/*.o
	@echo "*.o files deleted"

fclean: clean
	@rm -f $(NAME)
	@cd $(SUB_DIR) && $(MAKE) -s fclean
	@echo "fdf deleted"

re: fclean all