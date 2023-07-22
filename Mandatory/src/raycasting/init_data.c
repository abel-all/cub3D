/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-all <abel-all@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 13:12:08 by abel-all          #+#    #+#             */
/*   Updated: 2023/07/22 13:13:42 by abel-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

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
    data->img->img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
    data->img->addr = mlx_get_data_addr(data->img->img, \
    &data->img->bits_per_pixel, &data->img->line_length, &data->img->endian);
	data->img1 = malloc(sizeof(t_img));
    data->img1->img = mlx_new_image(data->mlx, 1920, 1080);
    data->img1->addr = mlx_get_data_addr(data->img1->img, \
    &data->img1->bits_per_pixel, &data->img1->line_length, &data->img1->endian);
	// mlx_put_image_to_window();
}

void	init_player(t_data *data)
{
	data->player->x = ((MAP_NUM_COLS * TILE_SIZE) / 2);
	data->player->y = ((MAP_NUM_ROWS * TILE_SIZE) / 2);
	data->player->height = 8;
	data->player->width = 8;
	data->player->turndirection = 0;
	data->player->walkdirection = 0;
	data->player->rotationangle = M_PI / 2;
	data->player->rotationspeed = 3 * (M_PI / 180);
	data->player->movespeed = 3;
	data->ray = malloc(sizeof(t_ray) * NUM_OF_RAYS);
}