# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abel-all <abel-all@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/22 11:49:07 by abel-all          #+#    #+#              #
#    Updated: 2023/07/24 13:28:46 by abel-all         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= 	cub3d

CFLAGS	=	-g #-Wall -Wextra -Werror

HEADERS	= 	lib/cub3d.h

SRCS	= 	src/cub3d.c src/raycasting/raycasting_calcule.c src/raycasting/player_movement.c \
			src/raycasting/utils_for_calcule.c src/raycasting/init_data.c \
			src/raycasting/player_movement.c\
			src/rendring/rendring_minimap.c src/rendring/rendring_utils.c src/rendring/rendring_walls.c

OBJS	= 	$(SRCS:.c=.o)

all		: 	$(NAME)

$(NAME)	: 	$(OBJS)
			cc $(CFLAGS) $^ -lmlx -framework OpenGL -framework AppKit -o $@

%.o		: 	%.c $(HEADERS)
			cc $(CFLAGS) -c $< -o $@

clean	:
			rm -rf $(OBJS)

fclean 	: 	clean
			rm -rf $(NAME)

re		: 	fclean all

.PHONY	: 	fclean all clean re