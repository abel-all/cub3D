/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-all <abel-all@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 14:42:16 by abel-all          #+#    #+#             */
/*   Updated: 2023/06/22 16:43:07 by abel-all         ###   ########.fr       */
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
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1}
};
//     for (size_t x = 0; x < 20; x++)
//     {
//            for (size_t y = 0; y < 20; y++)
//     {
//          if (type == 1)
//         mlx_pixel_put(data->mlx, data->mlx_win, x + posx, y +  posy  , 0xFFFFFF);
//     else
//         mlx_pixel_put(data->mlx, data->mlx_win,x + posx, y +  posy, 0x000000);
// }

//     }
    
// }

void    drawRectangle(int x, int y, int color, t_data *data)
{
    for (int i = x; i <= (x + TILE_SIZE); i++) {
        for (int j = y; j <= (y + TILE_SIZE); j++) {
            //drawPixel(i, j, color);
            if (color == 1)
                mlx_pixel_put(data->mlx, data->mlx_win, x, y , 0x00000000);
            else
                mlx_pixel_put(data->mlx, data->mlx_win, x, y, 0xFFFFFFFF);
        }
    }
}

void draw_rec(t_data *data)
{
    int tileColor;
    //0 :0xFFFFFFFF
    //1 :0x00000000
    for (int i = 0; i < MAP_NUM_ROWS; i++) {
            for (int j = 0; j < MAP_NUM_COLS; j++){
                if (map[i][j] == 1)
                    tileColor = 0;
                else
                    tileColor = 1;
                drawRectangle(j * TILE_SIZE, i * TILE_SIZE, tileColor, data);
            }
    }
}

// void    draw_grid(t_data *data, int j, int i)
// {
//     if (!map[i][j])
//         mlx_pixel_put(data->mlx, data->mlx_win, i * 32 , j * 32 , 0xFFFFFF);
//     else
//         mlx_pixel_put(data->mlx, data->mlx_win, i * 32 , j * 32 , 0x000000);
// }

// void    ft_draw(t_data *data)
// {
//     int	i;
// 	int	j;

// 	j = -1;
// 	while (++j < MAP_NUM_COLS)
// 	{
// 		i = -1;
// 		while (++i < MAP_NUM_ROWS)
//             draw_rec(data, i * 16 ,j * 16,map[i][j]);
// 			//draw_grid(data, j, i);;
// 	}
// }

void    setup_data(t_data *data)
{
    // size_x		:the width of the windows
    // size_y		:the heigth of the windows
    data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, 900, \
    600, "cub3D");
}

int	main()
{
	t_data	*data;

	data = malloc(sizeof(t_data));
    // TODO : initialaize the data
    setup_data(data);
    // TODO : draw frames
	// ft_draw(data);
    draw_rec(data);
	mlx_loop(data->mlx);
	return (0);
}