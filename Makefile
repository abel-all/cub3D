# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abel-all <abel-all@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/12 10:53:45 by ychahbi           #+#    #+#              #
#    Updated: 2023/08/12 13:38:49 by abel-all         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all bonus clean fclean re

all:
	@make -C Mandatory/
	@mv Mandatory/cub3D . 
bonus:
	@make -C Bonus/
	@mv Bonus/cub3D . 
clean: 
	@make clean -C Mandatory/
	@make clean -C Bonus/ 
fclean:
	@make fclean -C Mandatory/
	@make fclean -C Bonus/
	@rm -rf cub3D
re: fclean all
