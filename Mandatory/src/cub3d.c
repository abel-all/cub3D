/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-all <abel-all@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 12:37:20 by abel-all          #+#    #+#             */
/*   Updated: 2023/07/19 15:14:49 by abel-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/cub3d.h"



int	check_if_wall(t_data *data, double x, double y)
{
	int gridx;
	int gridy;

	if (x < 0 || x > WIN_WIDTH || y < 0 || y > WIN_HEIGHT)
		return (1);
	gridx = floor(x / TILE_SIZE);
	gridy = floor(y / TILE_SIZE);
	if (map[gridy][gridx] == 0)
		return (0);
	return (1);
}

int	check_if_insidemap(double x, double y, int winwidth, int winheight)
{
    if (x >= 0 && x <= winwidth && y >= 0 && y <= winheight)
		return (1);
	return (0);
}

void	draw_ray(t_data *data, t_ray *ray, int stripid)
{
	ray->a = malloc(sizeof(t_point));
	ray->b = malloc(sizeof(t_point));
	ray->a->x = data->player->x;
    ray->a->y = data->player->y;
    ray->b->x = ray->wallhitx;
    ray->b->y = ray->wallhity;
	draw_line(data, ray->a, ray->b);
	rendring3dprojectionwalls(data, ray, stripid);
}

double	get_normalizeangle(double angle)
{
	angle = remainder(angle, (2 * M_PI));
	if (angle < 0)
		angle = angle + (2 * M_PI);
	return (angle);
}

int	chek_if_isdown(t_ray *ray)
{
	if (ray->rayangle > 0 && ray->rayangle < M_PI)
		return (1);
	else
		return (0);
}

int	chek_if_isup(t_ray *ray)
{
	return (!chek_if_isdown(ray));
}

int	chek_if_isright(t_ray *ray)
{
	if (ray->rayangle < (0.5 * M_PI) || ray->rayangle > (1.5 * M_PI))
		return (1);
	else
		return (0);
}

int	chek_if_isleft(t_ray *ray)
{
	return (!chek_if_isright(ray));
}

void	init_ray(t_ray *ray, double rayangle)
{
	ray->rayangle = get_normalizeangle(rayangle);
	ray->isdown = chek_if_isdown(ray);
	ray->isup = chek_if_isup(ray);
	ray->isright = chek_if_isright(ray);
	ray->isleft = chek_if_isleft(ray);
	ray->distance = 0;
	ray->horzwallhitx = 0;
	ray->horzwallhity = 0;
	ray->vertwallhitx = 0;
	ray->vertwallhity = 0;
}

double	distance_betwn_ab(double x1, double y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void	cast_ray(t_data *data, t_ray *ray, double rayangle, int stripid)
{
	double	xintersept;
	double	yintersept;
	double	xstep;
	double	ystep;
	double	xcheck;
	double	ycheck;
	// double	horzwallhitx = 0;
	// double	horzwallhity = 0;
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
	draw_ray(data, ray, stripid);
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
	double	new_px;
	double	new_py;
	
	mlx_destroy_image(data->mlx, data->img->img);
	data->img->img = mlx_new_image(data->mlx, 1920, 1080);
    data->img->addr = mlx_get_data_addr(data->img->img, \
    &data->img->bits_per_pixel, &data->img->line_length, &data->img->endian);

	mlx_destroy_image(data->mlx, data->img1->img);
	data->img1->img = mlx_new_image(data->mlx, 1920, 1080);
    data->img1->addr = mlx_get_data_addr(data->img1->img, \
    &data->img1->bits_per_pixel, &data->img1->line_length, &data->img1->endian);
	
	// mlx_clear_window(data->mlx, data->mlx_win);
	data->player->rotationangle += data->player->turndirection * data->player->rotationspeed;
	data->player->rotationangle = get_normalizeangle(data->player->rotationangle);
	movestep = data->player->walkdirection * data->player->movespeed;
	new_px = data->player->x + cos(data->player->rotationangle) * movestep;
	new_py = data->player->y + sin(data->player->rotationangle) * movestep;
	if (!check_if_wall(data, new_px, new_py))
	{
		data->player->x = new_px;
		data->player->y = new_py;
	}
	// draw_player(data, data->player, 0, 0);
	rendring(data, data->player);
	castallrays(data, 0);
	// rendring3dprojectionwalls(data, -1);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img1->img, 0, 0);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img->img, 0, 0);
}

int	keypressed(int key_code, void	*param)
{
	t_data *data;

	data = (t_data *)param;
	if (key_code == W) //&& map[x->p_y - 1][x->p_x] != '1')
		data->player->walkdirection = 1;
	else if (key_code == S )//&& map[x->p_y + 1][x->p_x] != '1')
		data->player->walkdirection = -1;
	else if (key_code == D )//&& map[x->p_y][x->p_x + 1] != '1')
		data->player->turndirection = 1;
	else if (key_code == A )//&& map[x->p_y][x->p_x - 1] != '1')
		data->player->turndirection = -1;
	else if (key_code == ESC)
		exit(1);
	update(data);
	return (key_code);
}

int	keyreleased(int key_code, void	*param)
{
	t_data *data;

	data = (t_data *)param;
	if (key_code == W) //&& map[x->p_y - 1][x->p_x] != '1')
		data->player->walkdirection = 0;
	else if (key_code == S )//&& map[x->p_y + 1][x->p_x] != '1')
		data->player->walkdirection = 0;
	else if (key_code == D )//&& map[x->p_y][x->p_x + 1] != '1')
		data->player->turndirection = 0;
	else if (key_code == A )//&& map[x->p_y][x->p_x - 1] != '1')
		data->player->turndirection = 0;
	return (key_code);
}

int	exit_status(int key_code, void	*param)
{
	exit(EXIT_SUCCESS);
}

void	init_player(t_data *data)
{
	data->player->x = ((MAP_NUM_COLS * TILE_SIZE) / 2);
	data->player->y = ((MAP_NUM_ROWS * TILE_SIZE) / 2);
	data->player->height = 4;
	data->player->width = 4;
	data->player->turndirection = 0;
	data->player->walkdirection = 0;
	data->player->rotationangle = M_PI / 2;
	data->player->rotationspeed = 3 * (M_PI / 180);
	data->player->movespeed = 3.0;
	data->ray = malloc(sizeof(t_ray) * NUM_OF_RAYS);
}

int main()
{
	t_data	    *data;
	t_player	*player;
	t_img		*img;

	data = malloc(sizeof(t_data));
	player = malloc(sizeof(t_player));
	if (!data)
		ft_error(MALLOC_ERR);
    init_window(data, player);// is setup part
    init_player(data);// is setup part for player
	rendring(data, player);// rendring map and player
	mlx_put_image_to_window(data->mlx, data->mlx_win, \
	data->img1->img, 0, 0);
	mlx_put_image_to_window(data->mlx, data->mlx_win, \
	data->img->img, 0, 0);
	mlx_hook(data->mlx_win, 2, 0, keypressed, data);
	mlx_hook(data->mlx_win, 3, 0, keyreleased, data);
	mlx_hook(data->mlx_win, 17, 0, exit_status, NULL);
	// mlx_key_hook(data->mlx_win, keys_handler, data);
	mlx_loop(data->mlx);
}