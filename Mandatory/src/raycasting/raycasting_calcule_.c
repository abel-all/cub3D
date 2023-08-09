/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_calcule_.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychahbi <ychahbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 13:04:49 by abel-all          #+#    #+#             */
/*   Updated: 2023/08/08 18:52:59 by ychahbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

void	set_wallhit_corr(t_data *data, t_ray *ray, int f)
{
	if (!f)
	{
		ray->vertwallhitx = data->nexttouch.x;
		ray->vertwallhity = data->nexttouch.y;
		data->foundvertwallhit = 1;
	}
	else
	{
		ray->horzwallhitx = data->nexttouch.x;
		ray->horzwallhity = data->nexttouch.y;
		data->foundhorzwallhit = 1;
	}
}

static void	check_ray_direction(t_data *data, t_ray *ray, int f)
{
	if (!f)
	{
		if (ray->isleft == 1)
			data->check.x--;
	}
	else
	{
		if (ray->isup == 1)
			data->check.y--;
	}
}

void	increment_until_find_wall(t_data *data, t_ray *ray, int f)
{
	while (check_if_insidemap(data->nexttouch.x, data->nexttouch.y, \
	data->map_width, data->map_height) == 1)
	{
		data->check.x = data->nexttouch.x;
		data->check.y = data->nexttouch.y;
		check_ray_direction(data, ray, f);
		if (check_if_wall(data, data->check.x, data->check.y) == 1)
		{
			set_wallhit_corr(data, ray, f);
			break ;
		}
		else 
		{
			data->nexttouch.x += data->step.x;
			data->nexttouch.y += data->step.y;
		}
	}
}

void	calc_horzintersection(t_data *data, t_ray *ray)
{
	data->intersept.y = floor(data->player.y / TILE_SIZE) * TILE_SIZE;
	if (ray->isdown == 1)
		data->intersept.y += TILE_SIZE;
	data->intersept.x = data->player.x + ((data->intersept.y - \
	data->player.y) / tan(ray->rayangle));
	data->step.y = TILE_SIZE;
	if (ray->isup == 1)
		data->step.y *= -1;
	data->step.x = TILE_SIZE / tan(ray->rayangle);
	if (ray->isleft == 1 && data->step.x > 0)
		data->step.x *= -1;
	if (ray->isright == 1 && data->step.x < 0)
		data->step.x *= -1;
	data->nexttouch.x = data->intersept.x;
	data->nexttouch.y = data->intersept.y;
	data->foundhorzwallhit = 0;
	increment_until_find_wall(data, ray, 1);
}

void	calc_vertintersection(t_data *data, t_ray *ray)
{
	data->intersept.x = floor(data->player.x / TILE_SIZE) * TILE_SIZE;
	if (ray->isright == 1)
		data->intersept.x += TILE_SIZE;
	data->intersept.y = data->player.y + ((data->intersept.x - \
	data->player.x) * tan(ray->rayangle));
	data->step.x = TILE_SIZE;
	if (ray->isleft == 1)
		data->step.x *= -1;
	data->step.y = TILE_SIZE * tan(ray->rayangle);
	if (ray->isup == 1 && data->step.y > 0)
		data->step.y *= -1;
	if (ray->isdown == 1 && data->step.y < 0)
		data->step.y *= -1;
	data->nexttouch.x = data->intersept.x;
	data->nexttouch.y = data->intersept.y;
	data->foundvertwallhit = 0;
	increment_until_find_wall(data, ray, 0);
}
