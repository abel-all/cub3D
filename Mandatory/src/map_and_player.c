/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_and_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-all <abel-all@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 15:07:36 by abel-all          #+#    #+#             */
/*   Updated: 2023/07/10 07:52:01 by abel-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static const int map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1},
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
	data->mlx_win = mlx_new_window(data->mlx, MAP_NUM_COLS \
    * TILE_SIZE, MAP_NUM_ROWS * TILE_SIZE, "cub3D");
	if (!data->mlx_win)
		ft_error(NEW_WIN_ERR);
	data->player = player;
	data->img = malloc(sizeof(t_img));
    data->img->addr = mlx_get_data_addr(data->img->img, \
    &data->img->bits_per_pixel, &data->img->line_length, &data->img->endian);
	player->x = ((MAP_NUM_COLS * TILE_SIZE) / 2);
	player->y = ((MAP_NUM_ROWS * TILE_SIZE) / 2);
	player->height = 12;
	player->width = 12;
	player->line_height = 2;
	player->line_width = 2;
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

void	draw_player(t_data *data, t_player *player, int y, int x)
{
	int	x1;
	int	x2;
	int	y1;
	int	y2;

	x1 = player->x - (player->width / 2);
	x2 = player->x + (player->width / 2);
	y1 = player->y - (player->height / 2);
	y2 = player->y + (player->height / 2);
	x = x1 - 1;
    while (++x <= x2)
	{
		y = y1 - 1;
        while (++y <= y2)
            my_mlx_pixel_put(data->img, x, y, 0xFF0000);
	}
	x1 = player->x - (player->line_width / 2);
	x2 = player->x + (player->line_width / 2);
	y1 = player->y;
	y2 = y1 - 25;
	while (y1 >= y2)
        my_mlx_pixel_put(data->img, player->x, y1--, 0xFF0000);
}
