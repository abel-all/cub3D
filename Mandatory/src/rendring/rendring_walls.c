/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendring_walls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-all <abel-all@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:16:33 by abel-all          #+#    #+#             */
/*   Updated: 2023/08/03 11:53:53 by abel-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

void    rendring_walls(t_data *data, int stripid)
{
    data->x = -1;
    while (++data->x < WALL_STRIP_WIDTH)
    {
        data->y = -1;
        while (++data->y < data->wall_top)
            my_mlx_pixel_put(data->view, data->x + (stripid * WALL_STRIP_WIDTH), data->y, data->c);
        data->y =  data->wall_top - 1;
        while (++data->y < data->wall_bottom)
        {
            data->color = create_rgb(data->color_intensity, data->color_intensity, data->color_intensity);
            if (check_if_insidemap(data->x + (stripid * WALL_STRIP_WIDTH), data->y, WIN_WIDTH1, WIN_HEIGHT1))
                my_mlx_pixel_put(data->view, data->x + (stripid * WALL_STRIP_WIDTH), data->y, data->color);
        }
        data->y = data->wall_bottom - 1;
        while (++data->y < WIN_HEIGHT1)
            my_mlx_pixel_put(data->view, data->x + (stripid * WALL_STRIP_WIDTH), data->y, data->f);
    }
}

void    rendring3dprojectionwalls(t_data *data, t_ray *ray, int stripid)
{
    // calc the distance of projection plane :
    data->disprojplane = (WIN_WIDTH1 / 2) / tan(FOV_ANGLE / 2);
    // projected wall height :
    data->wallstripheight = (TILE_SIZE / (ray->distance * cos(ray->rayangle -\
    data->player->rotationangle))) * data->disprojplane;
    data->wall_top = (WIN_HEIGHT1 / 2) - (data->wallstripheight / 2);
    if (data->wall_top < 0)
        data->wall_top = 0;
    data->wall_bottom = data->wall_top + data->wallstripheight;
    if (data->wall_bottom >= WIN_HEIGHT1)
        data->wall_bottom = WIN_HEIGHT1 - 1;
    if (ray->washitvert == 1)
        data->color_intensity = 140;
    else
        data->color_intensity = 100;
    rendring_walls(data, stripid);
}

int	ft_rendring(void *param)
{
	t_data *data;

	data = (t_data *)param;
	rendring_minimap(data, 0, 0);
	int i = 0;
	while (i < NUM_OF_RAYS)
	{
	    rendring3dprojectionwalls(data, &data->ray[i], i);
		i++;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->view->img, 0, 0);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->minimap->img, 20, 850);
	return (1);
}
