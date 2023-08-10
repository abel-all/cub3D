# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abel-all <abel-all@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/22 11:49:07 by abel-all          #+#    #+#              #
#    Updated: 2023/08/10 11:40:24 by abel-all         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#NAME	= 	cub3D
#
#CFLAGS	=	-g -Wall -Wextra -Werror #-fsanitize=address
#
#HEADERS	= 	Mandatory/lib/cub3d.h Mandatory/lib/get_next_line.h
#
#BHEADERS	= 	Bonus/lib/cub3d_bonus.h Bonus/lib/get_next_line_bonus.h
#
#SRCS	= 	Mandatory/src/cub3d.c Mandatory/src/raycasting/raycasting_calcule.c Mandatory/src/raycasting/player_movement.c \
#			Mandatory/src/raycasting/utils_for_calcule.c Mandatory/src/raycasting/init_data.c Mandatory/src/raycasting/ray_direction.c\
#			Mandatory/src/raycasting/player_movement.c Mandatory/src/raycasting/raycasting_calcule_.c\
#			Mandatory/src/rendring/rendring_minimap.c Mandatory/src/rendring/rendring_utils.c Mandatory/src/rendring/rendring_walls.c \
#			Mandatory/src/parsing/parsing.c Mandatory/src/parsing/parsing_.c Mandatory/src/parsing/parsing__.c Mandatory/src/parsing/parsing___.c\
#			Mandatory/src/utils/ft_atoi.c Mandatory/src/utils/ft_split.c Mandatory/src/utils/ft_strcmp.c Mandatory/src/utils/ft_strdup.c \
#			Mandatory/src/utils/get_next_line.c Mandatory/src/utils/get_next_line_utils.c
#
#BSRCS	= 	Bonus/src/cub3d.c Bonus/src/raycasting/raycasting_calcule.c Bonus/src/raycasting/player_movement.c \
#			Bonus/src/raycasting/utils_for_calcule.c Bonus/src/raycasting/init_data.c Bonus/src/raycasting/ray_direction.c\
#			Bonus/src/raycasting/player_movement.c Bonus/src/raycasting/raycasting_calcule_.c\
#			Bonus/src/rendring/rendring_minimap.c Bonus/src/rendring/rendring_utils.c Bonus/src/rendring/rendring_walls.c \
#			Bonus/src/parsing/parsing.c Bonus/src/parsing/parsing_.c Bonus/src/parsing/parsing__.c Bonus/src/parsing/parsing___.c\
#			Bonus/src/utils/ft_atoi.c Bonus/src/utils/ft_split.c Bonus/src/utils/ft_strcmp.c Bonus/src/utils/ft_strdup.c \
#			Bonus/src/utils/get_next_line.c Bonus/src/utils/get_next_line_utils.c
#
#OBJS	= 	$(SRCS:.c=.o)
#
#BOBJS	= 	$(BSRCS:.c=.o)
#
#all		: 	$(NAME)
#
#$(NAME)	: 	$(OBJS)
#			cc $(CFLAGS) $^ -lmlx -framework OpenGL -framework AppKit -o $@
#
#bonus	:	$(BOBJS)
# 			cc $(CFLAGS) $^ -lmlx -framework OpenGL -framework AppKit $(NAME)
#
#%.o		: 	%.c $(HEADERS) $(BHEADERS)
#			cc $(CFLAGS) -c $< -o $@
#
#clean	:
#			rm -rf $(OBJS) $(BOBJS)
#
#fclean 	: 	clean
#			rm -rf $(NAME)
#
#re		: 	fclean all
#
#.PHONY	: 	fclean all clean re




NAME	= cub3D
CFLAGS	= -g -Wall -Wextra -Werror -Ofast #-fsanitize=address

HEADERS	= Mandatory/lib/cub3d.h Mandatory/lib/get_next_line.h
BHEADERS = Bonus/lib/cub3d_bonus.h Bonus/lib/get_next_line_bonus.h

SRCS	= Mandatory/src/cub3d.c Mandatory/src/raycasting/raycasting_calcule.c \
		  Mandatory/src/raycasting/player_movement.c Mandatory/src/raycasting/utils_for_calcule.c \
		  Mandatory/src/raycasting/init_data.c Mandatory/src/raycasting/ray_direction.c \
		  Mandatory/src/raycasting/raycasting_calcule_.c Mandatory/src/rendring/rendring_minimap.c \
		  Mandatory/src/rendring/rendring_utils.c Mandatory/src/rendring/rendring_walls.c \
		  Mandatory/src/parsing/parsing.c Mandatory/src/parsing/parsing_.c \
		  Mandatory/src/parsing/parsing__.c Mandatory/src/parsing/parsing___.c \
		  Mandatory/src/utils/ft_atoi.c Mandatory/src/utils/ft_split.c \
		  Mandatory/src/utils/ft_strcmp.c Mandatory/src/utils/ft_strdup.c \
		  Mandatory/src/utils/get_next_line.c Mandatory/src/utils/get_next_line_utils.c

BSRCS	= Bonus/src/cub3d.c Bonus/src/raycasting/raycasting_calcule.c \
		  Bonus/src/raycasting/player_movement.c Bonus/src/raycasting/utils_for_calcule.c \
		  Bonus/src/raycasting/init_data.c Bonus/src/raycasting/ray_direction.c \
		  Bonus/src/raycasting/raycasting_calcule_.c Bonus/src/rendring/rendring_minimap.c \
		  Bonus/src/rendring/rendring_utils.c Bonus/src/rendring/rendring_walls.c \
		  Bonus/src/parsing/parsing.c Bonus/src/parsing/parsing_.c \
		  Bonus/src/parsing/parsing__.c Bonus/src/parsing/parsing___.c \
		  Bonus/src/utils/ft_atoi.c Bonus/src/utils/ft_split.c \
		  Bonus/src/utils/ft_strcmp.c Bonus/src/utils/ft_strdup.c \
		  Bonus/src/utils/get_next_line.c Bonus/src/utils/get_next_line_utils.c

OBJS	= $(SRCS:.c=.o)
BOBJS	= $(BSRCS:.c=.o)

all		: $(NAME)

$(NAME)	: $(OBJS)
	cc $(CFLAGS) $^ -lmlx -framework OpenGL -framework AppKit -o $@

bonus	: $(BOBJS)
	cc $(CFLAGS) $^ -lmlx -framework OpenGL -framework AppKit -o $(NAME)

%.o		: %.c $(HEADERS) $(BHEADERS)
	cc $(CFLAGS) -c $< -o $@

clean	:
	rm -rf $(OBJS) $(BOBJS)

fclean	: clean
	rm -rf $(NAME)

re		: fclean all

.PHONY	: fclean all clean re
