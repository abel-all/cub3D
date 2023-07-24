/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendring_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-all <abel-all@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:13:53 by abel-all          #+#    #+#             */
/*   Updated: 2023/07/24 13:27:46 by abel-all         ###   ########.fr       */
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

void	new_draw_line(t_data *data, t_point *a, t_point *b)
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

int get_color(int x, int y)
{
	if (x < 0 || x > WIN_WIDTH  || y < 0 || y > WIN_HEIGHT)
	return 0xFF0000;
	int mx = x / TILE_SIZE;
	int my = y / TILE_SIZE;
	if (map[my][mx] == 1)
	 	return 0xBABABA;
	else 
	return 0x006600;	 
}