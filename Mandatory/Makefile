# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ychahbi <ychahbi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/22 11:49:07 by abel-all          #+#    #+#              #
#    Updated: 2023/08/12 11:19:05 by ychahbi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3D
CFLAGS	= -g -Wall -Wextra -Werror -Ofast #-fsanitize=address

HEADERS	= lib/cub3d.h

rm_cub3D = rm -rf ../cub3D

SRCS	= src/cub3d.c src/raycasting/raycasting_calcule.c \
		  src/raycasting/player_movement.c src/raycasting/utils_for_calcule.c \
		  src/raycasting/init_data.c src/raycasting/ray_direction.c \
		  src/raycasting/raycasting_calcule_.c src/rendring/rendring_minimap.c\
		  src/rendring/rendring_utils.c src/rendring/rendring_walls.c \
		  src/parsing/parsing.c src/parsing/parsing_.c \
		  src/parsing/parsing__.c src/parsing/parsing___.c \
		  src/utils/ft_atoi.c src/utils/ft_split.c \
		  src/utils/ft_strcmp.c src/utils/ft_strdup.c \
		  src/utils/get_next_line.c src/utils/get_next_line_utils.c

OBJS	= $(SRCS:.c=.o) 

all		: $(NAME)

$(NAME)	: $(OBJS) 
	cc $(CFLAGS) $^ -lmlx -framework OpenGL -framework AppKit -o $@

%.o		: %.c $(HEADERS)
	cc $(CFLAGS) -c $< -o $@

clean	:
	rm -rf $(OBJS)

fclean	: clean
	rm -rf $(NAME)
	$(rm_cub3D)

re		: fclean all

.PHONY	: fclean all clean re
