/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-all <abel-all@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 13:12:08 by abel-all          #+#    #+#             */
/*   Updated: 2023/07/24 17:49:11 by abel-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

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

void	init_window(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		ft_error(INIT_ERR);
	data->mlx_win = mlx_new_window(data->mlx, 1920, 1080, "cub3D");
	if (!data->mlx_win)
		ft_error(NEW_WIN_ERR);
	data->player = malloc(sizeof(t_player));
	if (!data->player)
		ft_error(MALLOC_ERR);
	data->minimap = malloc(sizeof(t_img));
	if (!data->minimap)
		ft_error(MALLOC_ERR);
    data->minimap->img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
    data->minimap->addr = mlx_get_data_addr(data->minimap->img, \
    &data->minimap->bits_per_pixel, &data->minimap->line_length, &data->minimap->endian);
	data->view = malloc(sizeof(t_img));
	if (!data->view)
		ft_error(MALLOC_ERR);
    data->view->img = mlx_new_image(data->mlx, 1920, 1080);
    data->view->addr = mlx_get_data_addr(data->view->img, \
    &data->view->bits_per_pixel, &data->view->line_length, &data->view->endian);
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