/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-all <abel-all@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 12:37:20 by abel-all          #+#    #+#             */
/*   Updated: 2023/07/16 15:03:17 by abel-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/cub3d.h"

void	rendring(t_data *data, t_player *player)
{
	draw_2d_map(data);
	draw_player(data, player, 0, 0);
}

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

int	check_if_insidemap(double x, double y)
{
    if (x >= 0 && x <= WIN_WIDTH && y >= 0 && y <= WIN_HEIGHT)
		return (1);
	return (0);
}

void	draw_ray(t_data *data, t_ray *ray)
{
	ray->a->x = data->player->x;
    ray->a->y = data->player->y;
    ray->b->x = ray->wallhitx;
    ray->b->y = ray->wallhity;
	draw_line(data, ray->a, ray->b);
}

void	cast_rays(t_data *data, t_ray *ray, int coulumnid)
{
	double	xintersept;
	double	yintersept;
	double	xstep;
	double	ystep;
	double	nexthorztouchx;
	double	nexthorztouchy;
	int		foundHorzWallHit = 0;
	// HORIZONTAL RAY-GRID INTERSECTION :
	// find the y_coordinate of the closest horizontal grid intersection :
	yintersept = floor(data->player->y / TILE_SIZE) * TILE_SIZE;
	if (ray->isdown)
		yintersept += TILE_SIZE;
	// find the x_coordinate of the closest horizontal grid intersection :
	xintersept = data->player->x + ((data->player->y - yintersept) / tan(ray->rayangle));
	// calculate the increment xstep & ystep :
	ystep = TILE_SIZE;
	if (ray->isup)
		ystep *= -1;
	xstep = TILE_SIZE / tan(ray->rayangle);
	if (ray->isleft && xstep > 0)
		xstep *= -1;
	if (ray->isright && xstep < 0)
		xstep *= -1;
	nexthorztouchx = xintersept;
	nexthorztouchy = yintersept;
	if (ray->isup)
		nexthorztouchy--;
	// increment xstep & ystep until we find a wall
	while (check_if_insidemap(nexthorztouchx, nexthorztouchy))
	{
        if (check_if_wall(data, nexthorztouchx, nexthorztouchy))
		{
            // found a wall hit
            ray->wallhitx = nexthorztouchx;
            ray->wallhity = nexthorztouchy;
			foundHorzWallHit = 1;
			draw_ray(data, ray);
            break;
        }
		else 
		{
            nexthorztouchx += xstep;
            nexthorztouchy += ystep;
        }
	}
}

double	get_normalizeangle(double angle)
{
	angle = fmod(angle, (2 * M_PI));
	if (angle < 0)
		return (angle + (2 * M_PI));
	return (angle);
}

void	draw_rays(t_data *data, t_ray *ray, double angle, int coulumnid)
{
	ray->rayangle = get_normalizeangle(angle);
	ray->a = malloc(sizeof(t_point));
	ray->b = malloc(sizeof(t_point));
	ray->a->x = data->player->x;
    ray->a->y = data->player->y;
    ray->b->x = data->player->x + cos(ray->rayangle) * 40;
    ray->b->y = data->player->y + sin(ray->rayangle) * 40;
    // draw_line(data, ray->a, ray->b);
	ray->distance = 0;
	ray->wallhitx = 0;
	ray->wallhity = 0;
	if (ray->rayangle > 0 && ray->rayangle < M_PI)
		ray->isdown = 1;
	else
		ray->isdown = 0;
	ray->isup = !ray->isdown;
	if (ray->rayangle < M_PI_2 || ray->rayangle > (3 * M_PI_2))
		ray->isright = 1;
	else
		ray->isright = 0;
	// ray->isright = ray->rayangle < M_PI_2 || ray->rayangle > (3 * M_PI_2);
	ray->isleft = !ray->isright;
	cast_rays(data, ray, coulumnid);
}

void	castallrays(t_data *data, int i)
{
	int		columnid;
	double	rayangle;

	columnid = 0;
	// data->ray = malloc(sizeof(t_ray *) * NUM_OF_RAYS);
	// awal ray :
	rayangle = data->player->rotationangle - (FOV_ANGLE / 2);
	//while (++i < NUM_OF_RAYS) // loop all columns casting the rays :
	while (++i < NUM_OF_RAYS) // loop all columns casting the rays :
	{
		draw_rays(data, &data->ray[i], rayangle, columnid);
		rayangle += (FOV_ANGLE / NUM_OF_RAYS);
		columnid++;
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
	// mlx_clear_window(data->mlx, data->mlx_win);
	data->player->rotationangle += data->player->turndirection * data->player->rotationspeed;
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
	castallrays(data, -1);
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
	data->img->img, 0, 0);
	mlx_hook(data->mlx_win, 2, 0, keypressed, data);
	mlx_hook(data->mlx_win, 3, 0, keyreleased, data);
	mlx_hook(data->mlx_win, 17, 0, exit_status, NULL);
	// mlx_key_hook(data->mlx_win, keys_handler, data);
	mlx_loop(data->mlx);
}