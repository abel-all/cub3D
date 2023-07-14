/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3dtest.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-all <abel-all@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 23:39:53 by abel-all          #+#    #+#             */
/*   Updated: 2023/07/14 00:40:53 by abel-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/cub3d.h"

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

void	rendring(t_data *data, t_player *player)
{
	draw_2d_map(data);// rendri
	draw_player(data, player, 0, 0);
}

void    initialize_window(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		ft_error(INIT_ERR);
	data->mlx_win = mlx_new_window(data->mlx, 1920, 1080, "cub3D");
	if (!data->mlx_win)
		ft_error(NEW_WIN_ERR);
	// data->point = malloc(sizeof(t_point));
	data->img = malloc(sizeof(t_img));
    data->img->img = mlx_new_image(data->mlx, 1920, 1080);
    data->img->addr = mlx_get_data_addr(data->img->img, \
    &data->img->bits_per_pixel, &data->img->line_length, &data->img->endian);
	data->player = malloc(sizeof(t_player));
}

void	processinput(void *ptr)
{
	t_data	*data;

	data = (t_data *)ptr;
	
}

void	move_player()
{
	
}

int	hook_key(int key_code, void	*param)
{
	t_data   *data;
	
	data =(t_data *) param;
	if (key_code == W) //&& map[x->p_y - 1][x->p_x] != '1')
		move_player();
	else if (key_code == S )//&& map[x->p_y + 1][x->p_x] != '1')
		move_player();
	else if (key_code == D )//&& map[x->p_y][x->p_x + 1] != '1')
		move_player();
	else if (key_code == A )//&& map[x->p_y][x->p_x - 1] != '1')
		move_player();
	else if (key_code == ESC)
		exit(1);
	return (key_code);
}

int main()
{
	t_data	    *data;

	data = malloc(sizeof(t_data));
	if (!data)
		ft_error(MALLOC_ERR);
    initialize_window(data);// is setup part
	rendring(data, player);// rendring map and player
	// mlx_loop_hook(data->mlx, &processinput, data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, \
	data->img->img, 0, 0);
	mlx_hook(data->mlx_win, 2, 0, hook_key, x);
	mlx_hook(data->mlx_win, 17, 0, exit_status, x);
	// mlx_key_hook();
	// mlx_key_hook(data->mlx_win, keys_handler, data);
	mlx_loop(data->mlx);
}