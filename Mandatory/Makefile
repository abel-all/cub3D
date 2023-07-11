# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abel-all <abel-all@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/22 11:49:07 by abel-all          #+#    #+#              #
#    Updated: 2023/07/11 16:53:02 by abel-all         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= 	cub3d

CFLAGS	= -g #-Wall -Wextra -Werror

HEADERS	= 	src/cub3d.h

SRCS	= 	src/cub3d.c src/map_and_player.c src/player_movement.c

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