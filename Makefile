# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/31 16:04:14 by cmansey           #+#    #+#              #
#    Updated: 2023/12/04 12:13:33 by cmansey          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
SRC = cub3D.c window.c hooks.c struct.c raycasting_1.c draw.c check_map.c main_parsing.c \
parsing_file1.c parsing_file2.c utils.c tab_to_space.c textures.c exit.c animation.c \
utils_bis.c main_init.c input.c hooks_bis.c raycasting_2.c
OBJ = $(SRC:.c=.o)

CC = gcc
RM = rm -f
CCFLAGS = -Wextra -Wall -Werror

LIBFT = libft

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIBFT) > /dev/null 2>&1
	@$(MAKE) -C mlx/ > /dev/null 2>&1
	$(CC) $(CCFLAGS) $(OBJ) -L$(LIBFT) -lft -Lmlx -lmlx -Imlx -Iincludes -framework OpenGL -framework AppKit -o $(NAME)

%.o: %.c
	$(CC) $(CCFLAGS) -I/usr/include -Imlx -O3 -c $< -o $@

clean:
	$(RM) $(OBJ)
	@make clean -C $(LIBFT) > /dev/null 2>&1
	@$(MAKE) clean -C mlx > /dev/null 2>&1

fclean: clean
	$(RM) $(NAME)
	@make fclean -C $(LIBFT) > /dev/null 2>&1

re: fclean all

debug: CCFLAGS += -fsanitize=address
debug: re
	./cub3D maps/map2.cub

.PHONY: all clean fclean re debug
