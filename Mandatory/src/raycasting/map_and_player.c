/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_and_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-all <abel-all@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 15:07:36 by abel-all          #+#    #+#             */
/*   Updated: 2023/07/22 13:26:00 by abel-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

int map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

void    my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + (x * (img->bits_per_pixel / 8)));
	*(unsigned int*)dst = color;
}


void    draw_grid(t_data *data, int x, int y, int color)
{
    int	i;
    int	j;

    i = -1;
    while (++i < TILE_SIZE)
    {
        j = -1;
        while (++j < TILE_SIZE)
        {
            if (color == 1)
                my_mlx_pixel_put(data->img, SCALE_FACTOR * (i + x), SCALE_FACTOR * (j + y), 0xFFFFFF);
                // mlx_pixel_put(data->mlx, data->mlx_win, i + x, j + y, 0xFFFFFF);
            else if (color == 0)
                my_mlx_pixel_put(data->img, SCALE_FACTOR * (i + x), SCALE_FACTOR * (j + y), 0x000000);
                // mlx_pixel_put(data->mlx, data->mlx_win, i + x, j + y, 0x000000);
        }
    }
}

void    draw_2d_map(t_data *data)
{
    int	i;
    int	j;

    i = -1;
    while (++i < MAP_NUM_ROWS)
    {
        j = -1;
        while (++j < MAP_NUM_COLS)
        {
            if (map[i][j] == 1)
                draw_grid(data, (j * TILE_SIZE), (i * TILE_SIZE), 1);
            else if (map[i][j] == 0)
                draw_grid(data, (j * TILE_SIZE), (i * TILE_SIZE), 0);
        }
    }
}

void	draw_line(t_data *data, t_point *a, t_point *b)
{
	double deltax = b->x - a->x;
	double deltay = b->y - a->y;
	int n_of_pixels = sqrt((deltax * deltax) + (deltay * deltay));
	double pixelx = a->x;
	double pixely = a->y;
	deltax /= n_of_pixels;
	deltay /= n_of_pixels;
	while (n_of_pixels--)
	{
		my_mlx_pixel_put(data->img, SCALE_FACTOR * pixelx, SCALE_FACTOR * pixely, 0xFF0000);
		pixelx += deltax;
		pixely += deltay;
	}
}

void	draw_player(t_data *data, t_player *player, int y, int x)
{
	int	x1;
	int	x2;
	int	y1;
	int	y2;
    t_point *a;
    t_point *b;

	x1 = player->x - (player->width / 2);
	x2 = player->x + (player->width / 2);
	y1 = player->y - (player->height / 2);
	y2 = player->y + (player->height / 2);
    a = malloc(sizeof(t_point));
    b = malloc(sizeof(t_point));;
	x = x1 - 1;
    while (++x <= x2)
	{
		y = y1 - 1;
        while (++y <= y2)
            my_mlx_pixel_put(data->img, SCALE_FACTOR * x, SCALE_FACTOR * y, 0xFF0000);
	}
    a->x = player->x;
    a->y = player->y;
    b->x = player->x + cos(data->player->rotationangle) * 30;
    b->y = player->y + sin(data->player->rotationangle) * 30;
    draw_line(data, a, b);
    // draw_line(data, NULL, NULL, M_PI_2);
	// x1 = player->x - (player->line_width / 2);
	// x2 = player->x + (player->line_width / 2);
	// y1 = player->y;
	// y2 = y1 - 25;
	// while (y1 >= y2)
    //     my_mlx_pixel_put(data->img, player->x, y1--, 0xFF0000);
}

void	rendring(t_data *data, t_player *player)
{
	draw_2d_map(data);
	draw_player(data, player, 0, 0);
}

int create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void    rendring3dprojectionwalls(t_data *data, t_ray *ray, int stripid)
{
    double  distanceprojectionplane;
    double  wallstripheight;
    int x;
    int y;
    double  wall_top;
    double  wall_bottom;
    int  color_intensity;
    // loop every ray in the array of struct of rays :
    // while (++i < NUM_OF_RAYS)
    // {
    // calc the distance of projection plane :
    distanceprojectionplane = (WIN_WIDTH1 / 2) / tan(FOV_ANGLE / 2);
    // projected wall height :
    wallstripheight = (TILE_SIZE / (ray->distance * cos(ray->rayangle - data->player->rotationangle))) * distanceprojectionplane;
    wall_top = (WIN_HEIGHT1 / 2) - (wallstripheight / 2);
    if (wall_top < 0)
        wall_top = 0;
    wall_bottom = wall_top + wallstripheight;
    if (wall_bottom >= WIN_HEIGHT1)
        wall_bottom = WIN_HEIGHT1 - 1;
    if (ray->washitvert == 1)
        color_intensity = 140;
    else
        color_intensity = 100;
    x = 0;
    while (x < WALL_STRIP_WIDTH)
    {
        y = 0;
        while (y < wall_top)
        {
            my_mlx_pixel_put(data->img1, x + (stripid * WALL_STRIP_WIDTH), y, create_rgb(0, 128, 255));
            y++;
        }
        y =  wall_top;
        while (y < wall_bottom)
        {
           int color = create_rgb(color_intensity, color_intensity, color_intensity);
            if (check_if_insidemap(x + (stripid * WALL_STRIP_WIDTH), y, WIN_WIDTH1, WIN_HEIGHT1))
                my_mlx_pixel_put(data->img1, x + (stripid * WALL_STRIP_WIDTH), y, color);
            y++;
        }
        y = wall_bottom;
        while (y < WIN_HEIGHT1)
        {
            my_mlx_pixel_put(data->img1, x + (stripid * WALL_STRIP_WIDTH), y, create_rgb(0, 102, 0));
            y++;
        }
        x++;
    }
}
