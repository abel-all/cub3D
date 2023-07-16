/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-all <abel-all@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 08:11:17 by abel-all          #+#    #+#             */
/*   Updated: 2023/07/15 15:49:20 by abel-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include <mlx.h>

# define W 13
# define S 1
# define D 2
# define A 0
# define ESC 53

#define TILE_SIZE 50
#define MAP_NUM_ROWS 10
#define MAP_NUM_COLS 14
#define WIN_WIDTH (MAP_NUM_COLS * TILE_SIZE) 
#define WIN_HEIGHT (MAP_NUM_ROWS * TILE_SIZE)
#define FOV_ANGLE (60 * (M_PI / 180))
#define WALL_STRIP_WIDTH 30
#define NUM_OF_RAYS (WIN_WIDTH / WALL_STRIP_WIDTH)

#define MALLOC_ERR "Malloc error!\n"
#define INIT_ERR "Mlx init error!\n"
#define NEW_WIN_ERR "Mlx new window error!\n"

extern int map[MAP_NUM_ROWS][MAP_NUM_COLS];

typedef struct s_point
{
	int	x;
	int y;
} t_point;

typedef struct s_player
{
	double	x;
	double	y;
	double	width;
	double	height;
	int		turndirection; // =0 / -1 for left, +1 for right
	int		walkdirection; // =0 / -1 for back, +1 for front
	double	rotationangle; // PI / 2
	double	movespeed; // 3.0
	double	rotationspeed; // 3 * (PI / 180) -> so 3 degree per frame
} t_player;

typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_data
{
	void		*mlx;
	void		*mlx_win;
	t_player	*player;
	t_img		*img;
	t_point		*point;
}				t_data;


int		ft_error(char *err);
void	init_window(t_data *data, t_player *player);
void    draw_2d_map(t_data *data);
void	draw_player(t_data *data, t_player *player, int y, int x);
int 	keys_handler(int key_code, void *param);
void    my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	draw_line(t_data *data, t_point *a, t_point *b);
#endif