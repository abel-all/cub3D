/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_for_calcule.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-all <abel-all@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 13:03:08 by abel-all          #+#    #+#             */
/*   Updated: 2023/08/13 12:50:02 by abel-all         ###   ########.fr       */
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

int	check_if_wall(t_data *data, double x, double y)
{
	int	gridx;
	int	gridy;
	int	ret;

	if (x < 0 || x > data->map_width || y < 0 || y > data->map_height)
		return (-1);
	gridx = x / TILE_SIZE;
	gridy = y / TILE_SIZE;
	ret = allowed(data->map[gridy][gridx], -2);
	if (data->map[gridy] && data->map[gridy][gridx])
		if (ret == 2)
			return (count_n_of_wall(data, x, y));
	return (1);
}
