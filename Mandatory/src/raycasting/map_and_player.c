/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_and_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-all <abel-all@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 15:07:36 by abel-all          #+#    #+#             */
/*   Updated: 2023/07/16 10:55:21 by abel-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

int map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

void    my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	ft_strlen(char *s)
{
	int	i;
	
	i = -1;
	while (s[++i])
		;
	return (i);
}

int	ft_error(char *err)
{
	write(2, err, ft_strlen(err));
	exit(EXIT_FAILURE);
}

void	init_window(t_data *data, t_player *player)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		ft_error(INIT_ERR);
	data->mlx_win = mlx_new_window(data->mlx, 1920, 1080, "cub3D");
	if (!data->mlx_win)
		ft_error(NEW_WIN_ERR);
	data->player = player;
	data->point = malloc(sizeof(t_point));
	data->img = malloc(sizeof(t_img));
    data->img->img = mlx_new_image(data->mlx, 1920, 1080);
    data->img->addr = mlx_get_data_addr(data->img->img, \
    &data->img->bits_per_pixel, &data->img->line_length, &data->img->endian);
	// mlx_put_image_to_window();
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
                my_mlx_pixel_put(data->img, i + x, j + y, 0xFFFFFF);
                // mlx_pixel_put(data->mlx, data->mlx_win, i + x, j + y, 0xFFFFFF);
            else if (color == 0)
                my_mlx_pixel_put(data->img, i + x, j + y, 0x000000);
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
                draw_grid(data, j * TILE_SIZE, i * TILE_SIZE, 1);
            else if (map[i][j] == 0)
                draw_grid(data, j * TILE_SIZE, i * TILE_SIZE, 0);
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
		my_mlx_pixel_put(data->img, pixelx, pixely, 0xFF0000);
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
            my_mlx_pixel_put(data->img, x, y, 0xFF0000);
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
