# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asadanow <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/16 14:30:00 by asadanow          #+#    #+#              #
#    Updated: 2023/05/16 14:30:02 by asadanow         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

SRC = ./src/main.c \
		./src/vec_math.c \
		./src/vec_math2.c \
		./src/check_hits.c \
		./src/hit_sphere.c \
		./src/hit_plane.c \
		./src/hit_cylinder.c \
		./src/lights.c \
		./src/utils.c \
		./src/utils_mlx.c \
		./src/hooks.c \
		./src/parsing/parsing1.c \
		./src/parsing/parsing2.c \
		./src/parsing/utils_parsing1.c \
		./src/parsing/utils_parsing2.c \
		./src/parsing/utils_parsing3.c \
		./src/get_next_line/get_next_line.c \
		./src/get_next_line/get_next_line_utils.c

LIBDIR = ./libft/

CC = gcc -Wall -Wextra -Werror

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	cd $(LIBDIR) && $(MAKE)
	$(CC) $(OBJ) ./libft/libft.a ./minilibx-linux/libmlx_Linux.a -lXext -lX11 -lz -o $(NAME) -lm

.c.o:
	$(CC) -I ./includes -I ./libft -I /usr/include -Iminilibx-linux -c $< -o $@

clean:
	/bin/rm -f $(OBJ)
	cd $(LIBDIR) && $(MAKE) clean

fclean: clean
	/bin/rm -f $(NAME)
	cd $(LIBDIR) && $(MAKE) fclean

bonus:	all

re: fclean all
