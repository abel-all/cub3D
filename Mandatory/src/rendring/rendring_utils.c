/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendring_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychahbi <ychahbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:13:53 by abel-all          #+#    #+#             */
/*   Updated: 2023/08/13 10:33:26 by ychahbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + (x * (img->bits_per_pixel / 8)));
	*(unsigned int *)dst = color;
}

unsigned int	my_mlx_pixel_get(t_addr img, int x, int y)
{
	unsigned int	*dst;

	dst = img.data_addr + (y * (img.size_line / 4) + x);
	return (*dst);
}

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

int	get_color(t_data *data, int x, int y)
{
	int	gridx;
	int	gridy;

	if (x < 0 || x > data->map_width || y < 0 || y > data->map_height)
		return (0xEEF36A);
	gridx = x / TILE_SIZE;
	gridy = y / TILE_SIZE;
	if (data->map[gridy] && data->map[gridy][gridx])
	{
		if (data->map[gridy][gridx] == '1')
			return (0x98B9AB);
		else if (data->map[gridy][gridx] == ' ')
			return (0xEEF36A);
		else if (allowed(data->map[gridy][gridx], -2) == 2)
			return (0x5171A5);
	}
	return (0xEEF36A);
}
