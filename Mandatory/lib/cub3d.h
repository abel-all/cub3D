/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-all <abel-all@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 08:11:17 by abel-all          #+#    #+#             */
/*   Updated: 2023/07/11 16:29:05 by abel-all         ###   ########.fr       */
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
#define PI 3.14159265359

#define MALLOC_ERR "Malloc error!\n"
#define INIT_ERR "Mlx init error!\n"
#define NEW_WIN_ERR "Mlx new window error!\n"

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
	int		turndirection; // -1 for left, +1 for right
	int		walkdirection; // -1 for back, +1 for front
	double	rotationangle;
	double	walkspeed;
	double	turnspeed;
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
int keys_handler(int key_code, void *param);


#endif