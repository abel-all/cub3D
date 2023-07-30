/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendring_minimap.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychahbi <ychahbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:10:43 by abel-all          #+#    #+#             */
/*   Updated: 2023/07/30 07:42:20 by ychahbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

void	rendring_map(t_data *data, int x, int y)
{
	double dis;

	x = data->player->x - (MINI_WIDTH / 2);
	y = data->player->y - (MINI_WIDTH / 2);
	data->i = -1;
	while (++data->i < MINI_WIDTH)
	{
		data->j = -1;
		while (++data->j < MINI_WIDTH)
		{
			dis =  sqrt(pow((MINI_WIDTH / 2) - data->i, 2) + pow((MINI_WIDTH / 2) - data->j, 2));
			if (dis  < ((MINI_WIDTH / 2) - 8))
				my_mlx_pixel_put(data->minimap, data->i, data->j, get_color(data, data->i + x, y + data->j));
			else if (dis >= ((MINI_WIDTH / 2) - 8) && dis < (MINI_WIDTH / 2) )
				my_mlx_pixel_put(data->minimap, data->i, data->j, 0xaa4500);
			else
				my_mlx_pixel_put(data->minimap, data->i, data->j, 0xff000000);
		}
	}
}

void	rendring_player_and_his_dir(t_data *data, int x, int y)
{
    t_point a;
    t_point b;

	x = (MINI_WIDTH / 2) - (data->player->width / 2);
	y = (MINI_WIDTH / 2) - (data->player->height / 2);
	data->i = -1;
    while (++data->i < data->player->width )
	{
		data->j = 1;
        while (++data->j < data->player->height )
            my_mlx_pixel_put(data->minimap, x + data->i, y + data->j, 0xFF0000);
	}
    a.x = (MINI_WIDTH / 2);
    a.y = (MINI_WIDTH / 2);
    b.x = (MINI_WIDTH / 2) + cos(data->player->rotationangle) * 10;
    b.y = (MINI_WIDTH / 2) + sin(data->player->rotationangle) * 10;
    draw_line(data, a, b);
}

void	rendring_minimap(t_data *data, int x, int y)
{
	rendring_map(data, x, y);
	rendring_player_and_his_dir(data, x, y);
}