/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendring_minimap.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychahbi <ychahbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:10:43 by abel-all          #+#    #+#             */
/*   Updated: 2023/08/07 17:06:30 by ychahbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

void	put_data_color(int stripid, t_addr *addr, t_data *data, int x)
{
	int	y;

	y = (addr->height * (data->y - data->wall_top)
			/ (data->wallstripheight));
	data->color = my_mlx_pixel_get(*addr, x, y);
	if (check_if_insidemap(data->x + (stripid * WALL_STRIP_WIDTH),
			data->y, WIN_WIDTH, WIN_HEIGHT))
	{
		my_mlx_pixel_put(&data->view, data->x + (stripid * WALL_STRIP_WIDTH),
			data->y, data->color);
	}
}

static int	check_bord(double i, double j)
{
	if (i > BORD_HEIGHT && i < (MINI_WIDTH - BORD_HEIGHT) && \
	j > BORD_HEIGHT && j < (MINI_WIDTH - BORD_HEIGHT))
		return (0);
	return (1);
}

void	rendring_map(t_data *data, int x, int y)
{
	x = data->player.x - (MINI_WIDTH / 2);
	y = data->player.y - (MINI_WIDTH / 2);
	data->i = -1;
	while (++data->i < MINI_WIDTH)
	{
		data->j = -1;
		while (++data->j < MINI_WIDTH)
		{
			if (!check_bord(data->i, data->j))
				my_mlx_pixel_put(&data->minimap, data->i, data->j, \
				get_color(data, data->i + x, y + data->j));
			else
				my_mlx_pixel_put(&data->minimap, data->i, data->j, 0x3F3047);
		}
	}
}

void	rendring_player_and_his_dir(t_data *data, int x, int y)
{
	t_point	a;
	t_point	b;

	x = (MINI_WIDTH / 2) - (data->player.height / 2);
	y = (MINI_WIDTH / 2) - (data->player.height / 2);
	data->i = -1;
	while (++data->i < data->player.height)
	{
		data->j = -1;
		while (++data->j < data->player.height)
			my_mlx_pixel_put(&data->minimap, x + data->i, y + data->j, \
			0xFF0000);
	}
	a.x = (MINI_WIDTH / 2);
	a.y = (MINI_WIDTH / 2);
	b.x = (MINI_WIDTH / 2) + cos(data->player.rotationangle) * LINE_LENGTH;
	b.y = (MINI_WIDTH / 2) + sin(data->player.rotationangle) * LINE_LENGTH;
	draw_line(data, a, b);
}

void	rendring_minimap(t_data *data, int x, int y)
{
	rendring_map(data, x, y);
	rendring_player_and_his_dir(data, x, y);
}
