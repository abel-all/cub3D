/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-all <abel-all@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 15:58:23 by abel-all          #+#    #+#             */
/*   Updated: 2023/08/13 08:57:16 by abel-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

int	exit_status(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	exit(free_resources(data));
}

int	keypressed(int key_code, void	*param)
{
	t_data	*data;

	data = (t_data *)param;
	if (key_code == W) 
		data->player.walkdirection = 1;
	else if (key_code == S)
		data->player.walkdirection = -1;
	else if (key_code == A) 
		data->player.left_right = 1;
	else if (key_code == D)
		data->player.left_right = -1;
	else if (key_code == KEY_RIGHT)
		data->player.turndirection = 1;
	else if (key_code == KEY_LEFT)
		data->player.turndirection = -1;
	else if (key_code == ESC)
		exit(free_resources(data));
	else
		return (0);
	update(data);
	return (0);
}
