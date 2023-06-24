/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-all <abel-all@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 14:42:16 by abel-all          #+#    #+#             */
/*   Updated: 2023/06/24 15:46:31 by abel-all         ###   ########.fr       */
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

// void draw_line(int start, t_point end, t_data *data) {
//     int dx = end.x - start.x;
//     int dy = end.y - start.y;
//     int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy); // Determine the number of steps based on the larger difference

//     float xIncrement = dx / (float) steps;
//     float yIncrement = dy / (float) steps;

//     float x = start.x;
//     float y = start.y;

//     for (int i = 0; i <= steps; i++) {
//         mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0xFFFFFF); // Set pixel color (white)

//         x += xIncrement;
//         y += yIncrement;
//     }
// }

void draw_player(t_data *data, t_player *player)
{
	int	x1;
	int	x2;
	int	y1;
	int	y2;

	x1 = player->x - (player->width / 2);
	x2 = player->x + (player->width / 2);
	y1 = player->y - (player->height / 2);
	y2 = player->y + (player->height / 2);
    for (int x = x1; x <= x2; x++) {
        for (int y = y1; y <= y2; y++) {
            mlx_pixel_put(data->mlx, data->mlx_win, x, y, 0xFF0000); // Set pixel color (red)
        }
    }
	x1 = player->x - (player->line_width / 2);
	x2 = player->x + (player->line_width / 2);
	y1 = player->y;
	y2 = player->y + 50;
	for (int x = x1; x <= x2; x++) {
		for (int y = y1; y <= y2; y++)
    	    mlx_pixel_put(data->mlx, data->mlx_win, x, y, 0x008000); // Set pixel color (green)
	}
}

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

void    setup_data(t_data *data, t_player *player)
{
    // size_x		:the width of the windows
    // size_y		:the heigth of the windows
    data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, MAP_NUM_COLS \
    * TILE_SIZE, MAP_NUM_ROWS * TILE_SIZE, "cub3D");
	player->x = ((MAP_NUM_COLS * TILE_SIZE) / 2);
	player->y = ((MAP_NUM_ROWS * TILE_SIZE) / 2);
	player->height = 12;
	player->width = 12;
	player->line_height = 4;
	player->line_width = 4;
}

int	main()
{
	t_data	    *data;
	t_player	*player;

	data = malloc(sizeof(t_data));
	player = malloc(sizeof(t_player));
    // TODO : initialaize the data
    setup_data(data, player);
    // TODO : draw frames
    draw_2d_map(data);
    // player_movement(data);
    draw_player(data, player);
	mlx_loop(data->mlx);
	return (0);
}