/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-all <abel-all@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 14:42:16 by abel-all          #+#    #+#             */
/*   Updated: 2023/07/11 10:12:48 by abel-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <mlx.h>
#include "cub3d.h"

typedef struct s_player {
    float x; // player's x-coordinate
    float y; // player's y-coordinate
    float dir_x; // player's direction vector x-component
    float dir_y; // player's direction vector y-component
    float plane_x; // camera plane vector x-component
    float plane_y; // camera plane vector y-component
    float move_speed; // player's movement speed
    float rot_speed; // player's rotation speed
} t_player;

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

void    abdessamad()
{
    printf("jfjffj");
}
void    abdessamaddf()
{
    printf("jfjffj");
}
void    abdessamadfdg()
{
    printf("jfjffj");
}
void    abdessamaddd()
{
    printf("jfjffj");
}

void init_player(t_player *player, int x, int y, float direction)
{
    player->x = x; // set player's initial position
    player->y = y;
    player->dir_x = cos(direction); // set player's initial direction
    player->dir_y = sin(direction);
    player->plane_x = -0.66 * player->dir_y; // set player's camera plane
    player->plane_y = 0.66 * player->dir_x;
    player->move_speed = 0.05; // set player's movement speed
    player->rot_speed = 0.05; // set player's rotation speed
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