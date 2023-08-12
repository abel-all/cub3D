/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-all <abel-all@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 15:58:23 by abel-all          #+#    #+#             */
/*   Updated: 2023/08/12 14:15:38 by abel-all         ###   ########.fr       */
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
	update(data);
	return (0);
}

int	check_if_wall__(t_data *data, double x, double y)
{
	int	gridx;
	int	gridy;
	int	ret;

	if (x < 0 || x > data->map_width || y < 0 || y > data->map_height)
		return (-1);
	gridx = x / TILE_SIZE;
	gridy = y / TILE_SIZE;
	ret = allowed(data->map[gridy][gridx], -2);
	if (data->map[gridy] && data->map[gridy][gridx])
		if (ret == 2)
			return (0);
	return (1);
}

int	count_n_of_wall(t_data *data, double x, double y)
{
	int	flag;

	flag = 0;
	if (check_if_wall__(data, x - 4, y))
		flag++;
	if (check_if_wall__(data, x + 4, y))
		flag++;
	if (check_if_wall__(data, x, y - 4))
		flag++;
	if (check_if_wall__(data, x, y + 4))
		flag++;
	if (flag == 2)
		return (1);
	return (0);
}
