/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendring_minimap.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychahbi <ychahbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:10:43 by abel-all          #+#    #+#             */
/*   Updated: 2023/08/08 00:00:03 by ychahbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

void	put_data_color(int stripid, t_addr *addr, t_data *data, int x)
{
	int	y;

	y = (addr->height * (data->y - data->wall_top)
			/ (data->wallstripheight));
	data->color = my_mlx_pixel_get(*addr, x, y);
	if (check_if_insidemap(data->x + (stripid * WALL_STRIP_WIDTH),
			data->y, WIN_WIDTH, WIN_HEIGHT))
	{
		my_mlx_pixel_put(&data->view, data->x + (stripid * WALL_STRIP_WIDTH),
			data->y, data->color);
	}
}
