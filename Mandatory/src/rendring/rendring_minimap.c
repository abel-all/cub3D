/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendring_minimap.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-all <abel-all@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:10:43 by abel-all          #+#    #+#             */
/*   Updated: 2023/07/24 13:11:26 by abel-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

void	rendring_minimap(t_data *data)
{
	int x,y,i,j;  
	int color;
	x = data->player->x - (MINI_WIDTH / 2);
	y = data->player->y - (MINI_WIDTH / 2);


	i = 0;
	while (i < MINI_WIDTH)
	{
		j = 0;
		while (j < MINI_WIDTH)
		{
			double dis =  sqrt(pow((MINI_WIDTH / 2) - i, 2) + pow((MINI_WIDTH / 2) - j, 2));
			if (dis  < ((MINI_WIDTH / 2) - 8))
			{
			color = get_color(i + x, y + j);
				my_mlx_pixel_put(data->img, i, j, color);
				
			}
			else if (dis >= ((MINI_WIDTH / 2) - 8) && dis < (MINI_WIDTH / 2) )
			my_mlx_pixel_put(data->img, i, j, 0xaa4500);
			else
				my_mlx_pixel_put(data->img, i, j, 0xff000000);
	
			j++;
		}
		i++;
	}
	
	x = (MINI_WIDTH / 2) - (data->player->width / 2);
	y= (MINI_WIDTH / 2) - (data->player->height / 2);

    t_point *a = malloc(sizeof(t_point));
    t_point *b = malloc(sizeof(t_point));
	i = 0;
    while (++i < data->player->width )
	{
		j = 0;
        while (++j < data->player->height )
            my_mlx_pixel_put(data->img, x + i, y + j, 0xFF0000);
	}
	
    a->x = (MINI_WIDTH / 2);
    a->y = (MINI_WIDTH / 2);
    b->x = (MINI_WIDTH / 2) + cos(data->player->rotationangle) * 15;
    b->y = (MINI_WIDTH / 2) + sin(data->player->rotationangle) * 15;
    new_draw_line(data, a, b);
}