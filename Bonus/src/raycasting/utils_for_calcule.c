/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_for_calcule.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-all <abel-all@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 13:03:08 by abel-all          #+#    #+#             */
/*   Updated: 2023/08/12 10:05:18 by abel-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

void	generate_new_player_corr(t_data *data, double *new_px, double *new_py)
{
	double	movestep;

	if (data->player.walkdirection != 0)
	{
		movestep = data->player.walkdirection * data->player.movespeed;
		*new_px = cos(data->player.rotationangle) * movestep;
		*new_py = sin(data->player.rotationangle) * movestep;
	}
	else if (data->player.left_right != 0)
	{
		movestep = data->player.left_right * data->player.movespeed;
		*new_px = cos(data->player.rotationangle - M_PI_2) * movestep;
		*new_py = sin(data->player.rotationangle - M_PI_2) * movestep;
	}
	else
	{
		*new_px = 0;
		*new_py = 0;
	}
}

void	create_img(t_data *data, t_img *img, int flag, int i)
{
	if (flag)
		mlx_destroy_image(data->mlx, img->img);
	if (i == 1)
		img->img = mlx_new_image(data->mlx, MINI_WIDTH, MINI_WIDTH);
	else if (i == 2)
		img->img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	img->addr = mlx_get_data_addr(img->img, \
	&img->bits_per_pixel, &img->line_length, &img->endian);
}

void	destroy_and_create_img(t_data *data)
{
	create_img(data, &data->minimap, 1, 1);
	create_img(data, &data->view, 1, 2);
}

int	check_if_insidemap(double x, double y, int winwidth, int winheight)
{
	if (x >= 0 && x <= winwidth && y >= 0 && y <= winheight)
		return (1);
	return (0);
}

int	wall_or_not_(t_data *data, int gridx, int gridy)
{
	int	ret;

	ret = allowed(data->map[gridy][gridx], -2);
	if (data->map[gridy] && data->map[gridy][gridx])
		if (ret == 2)
			return (0);
	return (1);
}

int	wall_or_not(t_data *data, int flag, int i, int j)
{
	if (flag == 1)
	{
		data->grid.x = (data->player.x + 1) / TILE_SIZE;
		data->grid.y = data->player.y / TILE_SIZE;
		data->_grid.x = (data->player.x) / TILE_SIZE;
		data->_grid.y = (data->player.y + 1) / TILE_SIZE;
	}
	else if (flag == 2)
	{
		data->grid.x = (data->player.x - 1) / TILE_SIZE;
		data->grid.y = data->player.y / TILE_SIZE;
		data->_grid.x = (data->player.x) / TILE_SIZE;
		data->_grid.y = (data->player.y + 1) / TILE_SIZE;
	}
	else if (flag == 3)
	{
		data->grid.x = (data->player.x - 1) / TILE_SIZE;
		data->grid.y = data->player.y / TILE_SIZE;
		data->_grid.x = (data->player.x) / TILE_SIZE;
		data->_grid.y = (data->player.y - 1) / TILE_SIZE;
	}
	else if (flag == 4)
	{
		data->grid.x = (data->player.x + 1) / TILE_SIZE;
		data->grid.y = data->player.y / TILE_SIZE;
		data->_grid.x = (data->player.x) / TILE_SIZE;
		data->_grid.y = (data->player.y - 1) / TILE_SIZE;
	}
	i = wall_or_not_(data, data->grid.x, data->grid.y);
	j = wall_or_not_(data, data->_grid.x, data->_grid.y);
	if (i && j)
		return (1);
	return (0);
}

int	check_if_wall_(t_data *data)
{
	data->rot_ray.rayangle = data->player.rotationangle;
	data->rot_ray.isdown = chek_if_isdown(&data->rot_ray);
	data->rot_ray.isup = chek_if_isup(&data->rot_ray);
	data->rot_ray.isright = chek_if_isright(&data->rot_ray);
	data->rot_ray.isleft = chek_if_isleft(&data->rot_ray);
	if (data->rot_ray.isup && data->rot_ray.isright)
		return (wall_or_not(data, 1, 0, 0));
	else if (data->rot_ray.isup && data->rot_ray.isleft)
		return (wall_or_not(data, 2, 0, 0));
	else if (data->rot_ray.isdown && data->rot_ray.isleft)
		return (wall_or_not(data, 3, 0, 0));
	else if (data->rot_ray.isdown && data->rot_ray.isright)
		return (wall_or_not(data, 4, 0, 0));
	return (0);
}

int	check_if_wall(t_data *data, double x, double y)
{
	int	gridx;
	int	gridy;
	int	ret;

	if (x < 0 || x > data->map_width || y < 0 || y > data->map_height)
		return (-1);
	gridx = floor(x / TILE_SIZE);
	gridy = floor(y / TILE_SIZE);
	ret = allowed(data->map[gridy][gridx], -2);
	if (data->map[gridy] && data->map[gridy][gridx])
		if (ret == 2)
			return (check_if_wall_(data));
	return (1);
}
