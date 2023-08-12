# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ychahbi <ychahbi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/12 10:53:45 by ychahbi           #+#    #+#              #
#    Updated: 2023/08/12 10:53:46 by ychahbi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all bonus clean fclean re

all:
	make -C Mandatory/
bonus:
	make -C Bonus/
clean:
	make clean -C Mandatory/
	make clean -C Bonus/
fclean:
	make fclean -C Mandatory/
	make fclean -C Bonus/
re: fclean all