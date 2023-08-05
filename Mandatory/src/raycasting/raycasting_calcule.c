/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_calcule.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-all <abel-all@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 13:00:29 by abel-all          #+#    #+#             */
/*   Updated: 2023/08/05 16:56:47 by abel-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

void	set_wallhit_corr(t_data *data, t_ray *ray, int f)
{
	if (!f)
	{
    	ray->vertwallhitx = data->nexttouchx;
    	ray->vertwallhity = data->nexttouchy; 
		data->foundvertwallhit = 1;	
	}
	else
	{
		ray->horzwallhitx = data->nexttouchx;
        ray->horzwallhity = data->nexttouchy; 
		data->foundhorzwallhit = 1;
	}
}

void	increment_until_find_wall(t_data *data, t_ray *ray, int f)
{
	while (check_if_insidemap(data->nexttouchx, data->nexttouchy, data->map_width, data->map_height) == 1)
	{
		data->xcheck = data->nexttouchx;
		data->ycheck = data->nexttouchy;
		if (!f)
		{
		if (ray->isleft == 1)
			data->xcheck--;
		}
		else
		{
			if (ray->isup == 1)
				data->ycheck--;
		}
    	if (check_if_wall(data, data->xcheck, data->ycheck) == 1)
		{
			set_wallhit_corr(data, ray, f);
    	    break;
    	}
		else 
		{
    	    data->nexttouchx += data->xstep;
    	    data->nexttouchy += data->ystep;
    	}
	}
}

void	calc_horzintersection(t_data *data, t_ray *ray)
{
	data->yintersept = floor(data->player->y / TILE_SIZE) * TILE_SIZE;
	if (ray->isdown == 1)
		data->yintersept += TILE_SIZE;
	data->xintersept = data->player->x + ((data->yintersept - data->player->y) / tan(ray->rayangle));
	// calculate the increment xstep & ystep :
	data->ystep = TILE_SIZE;
	if (ray->isup == 1)
		data->ystep *= -1;
	data->xstep = TILE_SIZE / tan(ray->rayangle);
	if (ray->isleft == 1 && data->xstep > 0)
		data->xstep *= -1;
	if (ray->isright == 1 && data->xstep < 0)
		data->xstep *= -1;
	data->nexttouchx = data->xintersept;
	data->nexttouchy = data->yintersept;
	// increment xstep & ystep until we find a wall
	data->foundhorzwallhit = 0;
	increment_until_find_wall(data, ray, 1);
}

void	calc_vertintersection(t_data *data, t_ray *ray)
{
	data->xintersept = floor(data->player->x / TILE_SIZE) * TILE_SIZE;
	if (ray->isright == 1)
		data->xintersept += TILE_SIZE;
	data->yintersept = data->player->y + ((data->xintersept - data->player->x) * tan(ray->rayangle));
	// calculate the increment xstep & ystep :
	data->xstep = TILE_SIZE;
	if (ray->isleft == 1)
		data->xstep *= -1;
	data->ystep = TILE_SIZE * tan(ray->rayangle);
	if (ray->isup == 1 && data->ystep > 0)
		data->ystep *= -1;
	if (ray->isdown == 1 && data->ystep < 0)
		data->ystep *= -1;
	data->nexttouchx = data->xintersept;
	data->nexttouchy = data->yintersept;
	// increment xstep & ystep until we find a wall
	data->foundvertwallhit = 0;
	increment_until_find_wall(data, ray, 0);
}

void	calc_horz_vert_hitdis(t_data *data, t_ray *ray)
{
	if (data->foundhorzwallhit == 1)
		data->horzhitdis = distance_betwn_ab(data->player->x, data->player->y, \
		ray->horzwallhitx, ray->horzwallhity);
	else
		data->horzhitdis = INT_MAX;
	if (data->foundvertwallhit == 1)
		data->verthitdis = distance_betwn_ab(data->player->x, data->player->y, \
		ray->vertwallhitx, ray->vertwallhity);
	else
		data->verthitdis = INT_MAX;
}

void	cast_ray(t_data *data, t_ray *ray, double rayangle, int stripid)
{
	init_ray(ray, rayangle);
	/*===============================================*/
	// HORIZONTAL RAY-GRID INTERSECTION PART :
	/*===============================================*/
	calc_horzintersection(data, ray);
	/*===============================================*/
	// VERTICAL RAY-GRID INTERSECTION PART :
	/*===============================================*/
	calc_vertintersection(data, ray);
	/*===============================================*/
	// calc horz & vert distances & choose the smallest one  :
	/*===============================================*/
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
	// awal ray :
	rayangle = data->player->rotationangle - (FOV_ANGLE / 2);
	while (i < NUM_OF_RAYS) // loop all columns casting the rays :
	{
		cast_ray(data, &data->ray[i], rayangle, i);
		rayangle += rayangle_incr;
		i++;
	}
}

void	update(t_data *data)
{
	double	new_px;
	double	new_py;
	
	destroy_and_create_img(data);
	data->player->rotationangle += data->player->turndirection * data->player->rotationspeed;
	data->player->rotationangle = get_normalizeangle(data->player->rotationangle);
	generate_new_player_corr(data, &new_px, &new_py);
	if (!check_if_wall(data, new_px + data->player->x, new_py + data->player->y))
	{
		data->player->x += new_px;
		data->player->y += new_py;
	}
	castallrays(data, 0);
}
