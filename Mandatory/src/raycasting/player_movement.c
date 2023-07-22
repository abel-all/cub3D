/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-all <abel-all@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 15:58:23 by abel-all          #+#    #+#             */
/*   Updated: 2023/07/22 13:11:09 by abel-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

int	exit_status(int key_code, void	*param)
{
	exit(EXIT_SUCCESS);
}

int	keypressed(int key_code, void	*param)
{
	t_data *data;

	data = (t_data *)param;
	if (key_code == W) 
		data->player->walkdirection = 1;
	else if (key_code == S )
		data->player->walkdirection = -1;
	else if (key_code == A) 
		data->player->left_right = 1;
	else if (key_code == D)
		data->player->left_right = -1;
	else if (key_code == KEY_RIGHT)
		data->player->turndirection = 1;
	else if (key_code == KEY_LEFT)
		data->player->turndirection = -1;
	else if (key_code == ESC)
		exit(1);
	update(data);
	data->player->turndirection = 0;
	data->player->walkdirection = 0;
	data->player->left_right = 0;
	return (key_code);
}
