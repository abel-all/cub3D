/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-all <abel-all@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 13:12:08 by abel-all          #+#    #+#             */
/*   Updated: 2023/08/12 14:59:30 by abel-all         ###   ########.fr       */
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
	data->mlx_win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!data->mlx_win)
		ft_error(NEW_WIN_ERR);
	create_img(data, &data->view, 0);
}

double	get_rot_angle(t_data *data)
{
	if (data->p_r == 'S')
		return (M_PI / 2);
	if (data->p_r == 'W')
		return (M_PI);
	if (data->p_r == 'N')
		return ((3 * M_PI) / 2);
	return (0);
}

void	init_player(t_data *data)
{
	data->player.x = (data->p_p[0] * TILE_SIZE) + (TILE_SIZE / 2);
	data->player.y = (data->p_p[1] * TILE_SIZE) + (TILE_SIZE / 2);
	data->player.height = PLAYER_HEIGHT;
	data->player.turndirection = 0;
	data->player.walkdirection = 0;
	data->player.left_right = 0;
	data->player.rotationangle = get_rot_angle(data);
	data->player.rotationspeed = 3 * (M_PI / 180);
	data->player.movespeed = 3;
}
