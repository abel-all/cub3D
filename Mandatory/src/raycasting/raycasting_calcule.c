/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_calcule.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-all <abel-all@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 13:00:29 by abel-all          #+#    #+#             */
/*   Updated: 2023/07/22 13:07:01 by abel-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

void	cast_ray(t_data *data, t_ray *ray, double rayangle, int stripid)
{
	double	xintersept;
	double	yintersept;
	double	xstep;
	double	ystep;
	double	xcheck;
	double	ycheck;
	double	nexthorztouchx;
	double	nexthorztouchy;
	int		foundhorzwallhit = 0;
	int		foundvertwallhit = 0;

	init_ray(ray, rayangle);
	
	/*===============================================*/
	// HORIZONTAL RAY-GRID INTERSECTION PART :
	/*===============================================*/
	yintersept = floor(data->player->y / TILE_SIZE) * TILE_SIZE;
	if (ray->isdown == 1)
		yintersept += TILE_SIZE;
	xintersept = data->player->x + ((yintersept - data->player->y) / tan(ray->rayangle));
	// calculate the increment xstep & ystep :
	ystep = TILE_SIZE;
	if (ray->isup == 1)
		ystep *= -1;
	xstep = TILE_SIZE / tan(ray->rayangle);
	if (ray->isleft == 1 && xstep > 0)
		xstep *= -1;
	if (ray->isright == 1 && xstep < 0)
		xstep *= -1;
	nexthorztouchx = xintersept;
	nexthorztouchy = yintersept;
	// increment xstep & ystep until we find a wall
	while (check_if_insidemap(nexthorztouchx, nexthorztouchy, WIN_WIDTH, WIN_HEIGHT) == 1)
	{
		xcheck = nexthorztouchx;
		ycheck = nexthorztouchy;
		if (ray->isup == 1)
			ycheck--;
        if (check_if_wall(data, xcheck, ycheck))
		{
            // found a wall hit
            ray->horzwallhitx = nexthorztouchx;
            ray->horzwallhity = nexthorztouchy; 
			foundhorzwallhit = 1;
			// draw_ray(data, ray);
            break;
        }
		else 
		{
            nexthorztouchx += xstep;
            nexthorztouchy += ystep;
        }
	}
	/*===============================================*/
	// VERTICAL RAY-GRID INTERSECTION PART :
	/*===============================================*/
	
	xintersept = floor(data->player->x / TILE_SIZE) * TILE_SIZE;
	if (ray->isright == 1)
		xintersept += TILE_SIZE;
	yintersept = data->player->y + ((xintersept - data->player->x) * tan(ray->rayangle));
	// calculate the increment xstep & ystep :
	xstep = TILE_SIZE;
	if (ray->isleft == 1)
		xstep *= -1;
	ystep = TILE_SIZE * tan(ray->rayangle);
	if (ray->isup == 1 && ystep > 0)
		ystep *= -1;
	if (ray->isdown == 1 && ystep < 0)
		ystep *= -1;
	double nextverttouchx = xintersept;
	double nextverttouchy = yintersept;
	// increment xstep & ystep until we find a wall
	while (check_if_insidemap(nextverttouchx, nextverttouchy, WIN_WIDTH, WIN_HEIGHT) == 1)
	{
		xcheck = nextverttouchx;
		ycheck = nextverttouchy;
		if (ray->isleft == 1)
			xcheck--;
        if (check_if_wall(data, xcheck, ycheck))
		{
            // found a wall hit
            ray->vertwallhitx = nextverttouchx;
            ray->vertwallhity = nextverttouchy; 
			foundvertwallhit = 1;
			// draw_ray(data, ray);
            break;
        }
		else 
		{
            nextverttouchx += xstep;
            nextverttouchy += ystep;
        }
	}
	/*===============================================*/
	// calc horz & vert distances & choose the smallest one  :
	/*===============================================*/
	double horzhitdis;
	if (foundhorzwallhit == 1)
		horzhitdis = distance_betwn_ab(data->player->x, data->player->y, \
		ray->horzwallhitx, ray->horzwallhity);
	else
		horzhitdis = INT_MAX;
	double verthitdis;
	if (foundvertwallhit == 1)
		verthitdis = distance_betwn_ab(data->player->x, data->player->y, \
		ray->vertwallhitx, ray->vertwallhity);
	else
		verthitdis = INT_MAX;
	if (verthitdis < horzhitdis)
	{
		ray->distance = verthitdis;
		ray->wallhitx = ray->vertwallhitx;
		ray->wallhity = ray->vertwallhity;
		ray->washitvert = 1;
	}
	else
	{
		ray->distance = horzhitdis;
		ray->wallhitx = ray->horzwallhitx;
		ray->wallhity = ray->horzwallhity;
		ray->washitvert = 0;
	}
	// draw_ray(data, ray, stripid);
}

void	castallrays(t_data *data, int i)
{
	int		stripid;
	double	rayangle;
	double	rayangle_incr;

	// i = 1;
	stripid = 0;
	rayangle_incr = FOV_ANGLE / NUM_OF_RAYS;
	// data->ray = malloc(sizeof(t_ray) * NUM_OF_RAYS);//88//
	// awal ray :
	rayangle = data->player->rotationangle - (FOV_ANGLE / 2);
	//while (++i < NUM_OF_RAYS) // loop all columns casting the rays :
	while (stripid < NUM_OF_RAYS) // loop all columns casting the rays :
	{
		cast_ray(data, &data->ray[stripid], rayangle, stripid);
		rayangle += rayangle_incr;
		stripid++;
	}
}

void	update(t_data *data)
{
	double	movestep;
	double	new_px = 0;
	double	new_py = 0;
	
	mlx_destroy_image(data->mlx, data->img->img);
	data->img->img = mlx_new_image(data->mlx, MINI_WIDTH, MINI_WIDTH);
    data->img->addr = mlx_get_data_addr(data->img->img, \
    &data->img->bits_per_pixel, &data->img->line_length, &data->img->endian);

	mlx_destroy_image(data->mlx, data->img1->img);
	data->img1->img = mlx_new_image(data->mlx, 1920, 1080);
    data->img1->addr = mlx_get_data_addr(data->img1->img, \
    &data->img1->bits_per_pixel, &data->img1->line_length, &data->img1->endian);
	
	data->player->rotationangle += data->player->turndirection * data->player->rotationspeed;
	data->player->rotationangle = get_normalizeangle(data->player->rotationangle);
	if (data->player->walkdirection != 0)
	{
		movestep = data->player->walkdirection * data->player->movespeed;
		new_px =  cos(data->player->rotationangle) * movestep;
		new_py = sin(data->player->rotationangle) * movestep;
	}
	else if (data->player->left_right != 0)
	{
		movestep = data->player->left_right * data->player->movespeed;
		new_px =  cos(data->player->rotationangle - M_PI_2) * movestep;
		new_py = sin(data->player->rotationangle - M_PI_2) * movestep;
	}
	if (!check_if_wall(data, new_px + data->player->x, new_py + data->player->y))
	{
		data->player->x += new_px;
		data->player->y += new_py;
	}
	castallrays(data, 0);
}