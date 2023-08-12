# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ychahbi <ychahbi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/12 10:53:45 by ychahbi           #+#    #+#              #
#    Updated: 2023/08/12 11:18:43 by ychahbi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all bonus clean fclean re

all:
	@make -C Mandatory/
	@cp -rf Mandatory/cub3D . 
bonus:
	@make -C Bonus/
	@cp -rf Bonus/cub3D . 
clean: 
	@make clean -C Mandatory/
	@make clean -C Bonus/ 
fclean:
	@make fclean -C Mandatory/
	@make fclean -C Bonus/
re: fclean all