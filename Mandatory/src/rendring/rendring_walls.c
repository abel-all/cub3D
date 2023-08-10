/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendring_walls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-all <abel-all@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:16:33 by abel-all          #+#    #+#             */
/*   Updated: 2023/08/10 14:21:46 by abel-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

// void	put_data_color(int stripid, t_addr *addr, t_data *data, int x)
// {
// 	int	y;
// int distanceFromTop = data->y + (data->wallstripheight / 2) - (WIN_HEIGHT / 2);
// 	y = (addr->height * (distanceFromTop / (data->wallstripheight)));
// 	data->color = my_mlx_pixel_get(*addr, x, y);
// 	if (check_if_insidemap(data->x + stripid,
// 			data->y, WIN_WIDTH, WIN_HEIGHT))
// 	{
// 		my_mlx_pixel_put(&data->view, data->x + stripid,
// 			data->y, data->color);
// 	}
// }

void	init_of_pos(int stripid, t_data *data)
{
	data->pos.x1 = (fmod(data->ray[stripid].wallhitx, TILE_SIZE)
			/ TILE_SIZE) * data->addr_so.width;
	data->pos.x2 = (fmod(data->ray[stripid].wallhitx, TILE_SIZE)
			/ TILE_SIZE) * data->addr_no.width;
	data->pos.y1 = (fmod(data->ray[stripid].wallhity, TILE_SIZE)
			/ TILE_SIZE) * data->addr_ea.width;
	data->pos.y2 = (fmod(data->ray[stripid].wallhity, TILE_SIZE)
			/ TILE_SIZE) * data->addr_we.width;
}

void	rand_wall_textures(t_data *data, int stripid)
{
	while (++data->y < data->wall_bottom)
	{
		if (!data->ray[stripid].washitvert)
		{
			if (data->ray[stripid].isup)
				put_data_color(stripid, &data->addr_no, data, data->pos.x2);
			else
				put_data_color(stripid, &data->addr_so, data, data->pos.x1);
		}
		else
		{
			if (data->ray[stripid].isright)
				put_data_color(stripid, &data->addr_ea, data, data->pos.y1);
			else
				put_data_color(stripid, &data->addr_we, data, data->pos.y2);
		}
	}
}

void	rendring_walls(t_data *data, int stripid)
{
	// data->x = -1;
	// while (++data->x < 1)
	// {
		data->y = -1;
		while (++data->y < data->wall_top)
			my_mlx_pixel_put(&data->view, stripid
				, data->y, create_rgb(0, 128, 255));
		data->y = data->wall_top - 1;
		init_of_pos(stripid, data);
		// if (data->wallstripheight > 16000)
		// 	data->y = 0;
		rand_wall_textures(data, stripid);
		data->y = data->wall_bottom - 1;
		while (++data->y < WIN_HEIGHT)
			my_mlx_pixel_put(&data->view, stripid
				, data->y, create_rgb(0, 102, 0));
	// }
}

void	rendring3dprojectionwalls(t_data *data, t_ray *ray, int stripid)
{
	data->disprojplane = (WIN_WIDTH / 2) / tan(FOV_ANGLE / 2);
	data->wallstripheight = (TILE_SIZE / (ray->distance * \
	cos(ray->rayangle - data->player.rotationangle))) * data->disprojplane;
	data->wall_top = (WIN_HEIGHT / 2) - (data->wallstripheight / 2);
	if (data->wall_top < 0)
		data->wall_top = 0;
	data->wall_bottom = data->wall_top + data->wallstripheight;
	if (data->wall_bottom >= WIN_HEIGHT)
		data->wall_bottom = WIN_HEIGHT - 1;
	rendring_walls(data, stripid);
}

int	ft_rendring(void *param)
{
	t_data	*data;
	int		i;

	data = (t_data *)param;
	rendring_minimap(data, 0, 0);
	i = -1;
	while (++i < NUM_OF_RAYS)
		rendring3dprojectionwalls(data, &data->ray[i], i);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->view.img, 0, 0);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->minimap.img, \
	20, 850);
	return (1);
}
