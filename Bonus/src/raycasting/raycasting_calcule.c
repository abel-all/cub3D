/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_calcule.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychahbi <ychahbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 13:00:29 by abel-all          #+#    #+#             */
/*   Updated: 2023/08/09 10:08:59 by ychahbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

double	get_normalizeangle(double angle)
{
	angle = remainder(angle, (2 * M_PI));
	if (angle < 0)
		angle = angle + (2 * M_PI);
	return (angle);
}

void	calc_horz_vert_hitdis(t_data *data, t_ray *ray)
{
	if (data->foundhorzwallhit == 1)
		data->horzhitdis = distance_betwn_ab(data->player.x, data->player.y, \
		ray->horzwallhitx, ray->horzwallhity);
	else
		data->horzhitdis = INT_MAX;
	if (data->foundvertwallhit == 1)
		data->verthitdis = distance_betwn_ab(data->player.x, data->player.y, \
		ray->vertwallhitx, ray->vertwallhity);
	else
		data->verthitdis = INT_MAX;
}

void	cast_ray(t_data *data, t_ray *ray, double rayangle)
{
	init_ray(ray, rayangle);
	calc_horzintersection(data, ray);
	calc_vertintersection(data, ray);
	calc_horz_vert_hitdis(data, ray);
	if (data->verthitdis < data->horzhitdis)
	{
		ray->distance = data->verthitdis;
		ray->wallhitx = ray->vertwallhitx;
		ray->wallhity = ray->vertwallhity;
		ray->washitvert = 1;
	}
	else
	{
		ray->distance = data->horzhitdis;
		ray->wallhitx = ray->horzwallhitx;
		ray->wallhity = ray->horzwallhity;
		ray->washitvert = 0;
	}
}

void	castallrays(t_data *data, int i)
{
	double	rayangle;
	double	rayangle_incr;

	rayangle_incr = FOV_ANGLE / NUM_OF_RAYS;
	rayangle = data->player.rotationangle - (FOV_ANGLE / 2);
	while (++i < NUM_OF_RAYS)
	{
		cast_ray(data, &data->ray[i], rayangle);
		rayangle += rayangle_incr;
	}
}

void	update(t_data *data)
{
	double	new_px;
	double	new_py;

	destroy_and_create_img(data);
	data->player.rotationangle += data->player.turndirection * \
	data->player.rotationspeed;
	data->player.rotationangle = get_normalizeangle(data->player.rotationangle);
	generate_new_player_corr(data, &new_px, &new_py);
	if (!check_if_wall(data, new_px + data->player.x, new_py + data->player.y))
	{
		data->player.x += new_px;
		data->player.y += new_py;
	}
	castallrays(data, -1);
}
