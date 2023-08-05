/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-all <abel-all@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 13:12:08 by abel-all          #+#    #+#             */
/*   Updated: 2023/08/05 17:07:39 by abel-all         ###   ########.fr       */
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
	create_img(data, data->minimap, 0, 1);
	data->view = malloc(sizeof(t_img));
	if (!data->view)
		ft_error(MALLOC_ERR);
	create_img(data, data->view, 0, 2);
}

void	init_player(t_data *data)
{
	data->player->x = (data->p_p[0] * TILE_SIZE) + (TILE_SIZE / 2);
	data->player->y = (data->p_p[1] * TILE_SIZE) + (TILE_SIZE / 2);
	data->player->height = 4;
	data->player->turndirection = 0;
	data->player->walkdirection = 0;
	data->player->left_right = 0;
	data->player->rotationangle = M_PI / 2;
	data->player->rotationspeed = 3 * (M_PI / 180);
	data->player->movespeed = 2;
}
