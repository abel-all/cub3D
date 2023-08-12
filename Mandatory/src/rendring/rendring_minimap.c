/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendring_minimap.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychahbi <ychahbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:10:43 by abel-all          #+#    #+#             */
/*   Updated: 2023/08/12 18:16:50 by ychahbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

void	put_data_color(int stripid, t_addr *addr, t_data *data, int x)
{
	int	y;
	int	dis;

	dis = data->y + (data->wallstripheight / 2) - (WIN_HEIGHT / 2);
	y = (addr->height * (dis / (data->wallstripheight)));
	data->color = my_mlx_pixel_get(*addr, x, y);
	if (check_if_insidemap(data->x + stripid,
			data->y, WIN_WIDTH, WIN_HEIGHT))
	{
		my_mlx_pixel_put(&data->view, data->x + stripid,
			data->y, data->color);
	}
}
