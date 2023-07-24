/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendring_walls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-all <abel-all@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:16:33 by abel-all          #+#    #+#             */
/*   Updated: 2023/07/24 13:19:50 by abel-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

void    rendring3dprojectionwalls(t_data *data, t_ray *ray, int stripid)
{
    double  distanceprojectionplane;
    double  wallstripheight;
    int x;
    int y;
    double  wall_top;
    double  wall_bottom;
    int  color_intensity;
    // calc the distance of projection plane :
    distanceprojectionplane = (WIN_WIDTH1 / 2) / tan(FOV_ANGLE / 2);
    // projected wall height :
    wallstripheight = (TILE_SIZE / (ray->distance * cos(ray->rayangle - data->player->rotationangle))) * distanceprojectionplane;
    wall_top = (WIN_HEIGHT1 / 2) - (wallstripheight / 2);
    if (wall_top < 0)
        wall_top = 0;
    wall_bottom = wall_top + wallstripheight;
    if (wall_bottom >= WIN_HEIGHT1)
        wall_bottom = WIN_HEIGHT1 - 1;
    if (ray->washitvert == 1)
        color_intensity = 140;
    else
        color_intensity = 100;
    x = 0;
    while (x < WALL_STRIP_WIDTH)
    {
        y = 0;
        while (y < wall_top)
        {
            my_mlx_pixel_put(data->img1, x + (stripid * WALL_STRIP_WIDTH), y, create_rgb(0, 128, 255));
            y++;
        }
        y =  wall_top;
        while (y < wall_bottom)
        {
           int color = create_rgb(color_intensity, color_intensity, color_intensity);
            if (check_if_insidemap(x + (stripid * WALL_STRIP_WIDTH), y, WIN_WIDTH1, WIN_HEIGHT1))
                my_mlx_pixel_put(data->img1, x + (stripid * WALL_STRIP_WIDTH), y, color);
            y++;
        }
        y = wall_bottom;
        while (y < WIN_HEIGHT1)
        {
            my_mlx_pixel_put(data->img1, x + (stripid * WALL_STRIP_WIDTH), y, create_rgb(0, 102, 0));
            y++;
        }
        x++;
    }
}

int	ft_rendring(void *param)
{
	t_data *data;

	data = (t_data *)param;
	rendring_minimap(data);
	int i = 0;
	while (i < NUM_OF_RAYS)
	{
	rendring3dprojectionwalls(data, &data->ray[i], i);
		i++;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img1->img, 0, 0);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img->img, 20, 850);
	return (1);
}