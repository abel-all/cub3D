/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendring_minimap.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-all <abel-all@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:10:43 by abel-all          #+#    #+#             */
/*   Updated: 2023/08/10 14:41:08 by abel-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

void	put_data_color(int stripid, t_addr *addr, t_data *data, int x)
{
	int	y;
int distanceFromTop = data->y + (data->wallstripheight / 2) - (WIN_HEIGHT / 2);
	y = (addr->height * (distanceFromTop / (data->wallstripheight)));
	data->color = my_mlx_pixel_get(*addr, x, y);
	if (check_if_insidemap(data->x + stripid,
			data->y, WIN_WIDTH, WIN_HEIGHT))
	{
		my_mlx_pixel_put(&data->view, data->x + stripid,
			data->y, data->color);
	}
}
