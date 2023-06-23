/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-all <abel-all@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 14:42:16 by abel-all          #+#    #+#             */
/*   Updated: 2023/06/23 11:56:32 by abel-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h" 

static const int map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

void    rendermapgrid(t_data *data, int x, int y, int color)
{
    int i;
    int j;

    i = -1;
    while (++i < TILE_SIZE)
    {
        j = -1;
        while (++j < TILE_SIZE)
        {
            if (color == 1)
                mlx_pixel_put(data->mlx, data->mlx_win, i + x, j + y, 0x808080);
            else if (color == 0)
                mlx_pixel_put(data->mlx, data->mlx_win, i + x, j + y, 0xFFFFFF);
        }
    }
}

void    draw_2d_map(t_data *data)
{
    int i;
    int j;

    i = -1;
    while (++i < MAP_NUM_ROWS)
    {
        j = -1;
        while (++j < MAP_NUM_COLS)
        {
            if (map[i][j] == 1)
                rendermapgrid(data, j * TILE_SIZE, i * TILE_SIZE, 1);
            else if (map[i][j] == 0)
                rendermapgrid(data, j * TILE_SIZE, i * TILE_SIZE, 0);
        }
    }
}

void    setup_data(t_data *data)
{
    // size_x		:the width of the windows
    // size_y		:the heigth of the windows
    data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, MAP_NUM_COLS \
    * TILE_SIZE, MAP_NUM_ROWS * TILE_SIZE, "cub3D");
}

int	main()
{
	t_data	*data;

	data = malloc(sizeof(t_data));
    // TODO : initialaize the data
    setup_data(data);
    // TODO : draw frames
    draw_2d_map(data);
	mlx_loop(data->mlx);
	return (0);
}