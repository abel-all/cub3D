/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendring_walls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychahbi <ychahbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:16:33 by abel-all          #+#    #+#             */
/*   Updated: 2023/08/11 07:04:48 by ychahbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

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
	data->y = -1;
	while (++data->y < data->wall_top)
		my_mlx_pixel_put(&data->view, stripid, data->y, data->c);
	data->y = data->wall_top - 1;
	init_of_pos(stripid, data);
	rand_wall_textures(data, stripid);
	data->y = data->wall_bottom - 1;
	while (++data->y < WIN_HEIGHT)
		my_mlx_pixel_put(&data->view, stripid, data->y, data->f);
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
	double	rayangle;
	double	rayangle_incr;

	data = (t_data *)param;
	rayangle_incr = FOV_ANGLE / NUM_OF_RAYS;
	rayangle = data->player.rotationangle - (FOV_ANGLE / 2);
	i = -1;
	while (++i < NUM_OF_RAYS)
	{
		cast_ray(data, &data->ray[i], rayangle);
		rendring3dprojectionwalls(data, &data->ray[i], i);
		rayangle += rayangle_incr;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->view.img, 0, 0);
	return (1);
}
