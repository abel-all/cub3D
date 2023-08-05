/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendring_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-all <abel-all@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:13:53 by abel-all          #+#    #+#             */
/*   Updated: 2023/08/05 18:56:34 by abel-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

void    my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + (x * (img->bits_per_pixel / 8)));
	*(unsigned int*)dst = color;
}

int create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	draw_line(t_data *data, t_point a, t_point b)
{
	int n_of_pixels;

	data->deltax = b.x - a.x;
	data->deltay = b.y - a.y;
	n_of_pixels = sqrt((data->deltax * data->deltax) + (data->deltay * data->deltay));
	data->pixelx = a.x;
	data->pixely = a.y;
	data->deltax /= n_of_pixels;
	data->deltay /= n_of_pixels;
	while (n_of_pixels--)
	{
		my_mlx_pixel_put(data->minimap, data->pixelx, data->pixely, 0xFF0000);
		data->pixelx += data->deltax;
		data->pixely += data->deltay;
	}
}

int	get_color(t_data *data, int x, int y)
{
	int	tx;
	int	ty;

	if (x < 0 || x > data->map_width || y < 0 || y > data->map_height)
		return (0x009D9C);
	tx = x / TILE_SIZE;
	ty = y / TILE_SIZE;
	if (data->map[ty] && data->map[ty][tx])
	{
		if (data->map[ty][tx] == '1')
			return (0xBABABA);
		else if (data->map[ty][tx] == ' ')
			return (0x009D9C);
		else if (allowed(data->map[ty][tx], -2) == 2)
			return (0x000000);
	}
	return (0x009D9C);
}
