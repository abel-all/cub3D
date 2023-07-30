/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychahbi <ychahbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 08:11:17 by abel-all          #+#    #+#             */
/*   Updated: 2023/07/30 07:54:21 by ychahbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include <limits.h>
# include <mlx.h>

# define W 13
# define S 1
# define D 2
# define A 0
# define ESC 53
# define KEY_LEFT 123
# define KEY_RIGHT 124

# define TILE_SIZE 20
# define MAP_NUM_ROWS 10
# define MAP_NUM_COLS 14
# define WIN_WIDTH (MAP_NUM_COLS * TILE_SIZE)
# define WIN_HEIGHT (MAP_NUM_ROWS * TILE_SIZE)
# define WIN_WIDTH1 1920
# define WIN_HEIGHT1 1080
# define MINI_WIDTH 200
# define FOV_ANGLE (60 * (M_PI / 180))
# define WALL_STRIP_WIDTH 1
# define NUM_OF_RAYS (WIN_WIDTH1 / WALL_STRIP_WIDTH)
# define SCALE_FACTOR 0.5
# define MALLOC_ERR "Malloc error!\n"
# define INIT_ERR "Mlx init error!\n"
# define NEW_WIN_ERR "Mlx new window error!\n"

extern int map[MAP_NUM_ROWS][MAP_NUM_COLS];

typedef struct s_point
{
	double	x;
	double	y;
}				t_point;

typedef struct s_ray
{
	double	rayangle;
	double	wallhitx;
	double	wallhity;
	double	horzwallhitx;
	double	horzwallhity;
	double	vertwallhitx;
	double	vertwallhity;
	double	distance;
	int		washitvert;
	int		isdown;
	int		isup;
	int		isright;
	int		isleft;
	int		id;
	t_point	*a;
	t_point	*b;
}				t_ray;

typedef struct s_player
{
	double	x;
	double	y;
	double	width;
	double	height;
	int		left_right;
	int		turndirection; // =0 / -1 for left, +1 for right
	int		walkdirection; // =0 / -1 for back, +1 for front
	double	rotationangle; // PI / 2
	double	movespeed; // 3.0
	double	rotationspeed; // 3 * (PI / 180) -> so 3 degree per frame
} t_player;

typedef	struct s_img {
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
	double		wall_width;
	double		wall_height;
	char		**map;
	char		*mapname;
	char		p_r;
	int			p_p[2];
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	int			c;
	int			f;
	int			l_line;
	t_player	*player;
	t_img		*minimap;
	t_img		*view;
	t_point		*point;
	t_ray		*ray;
	double		xintersept;
	double		yintersept;
	double		xstep;
	double		ystep;
	double		nexttouchx;
	double		nexttouchy;
	double		xcheck;
	double		ycheck;
	int			foundhorzwallhit;
	int			foundvertwallhit;
	double		horzhitdis;
	double		verthitdis;
	int			i;
	int			j;
	double		deltax;
	double		deltay;
	double		pixelx;
	double		pixely;
	double		disprojplane;
	double		wallstripheight;
	int			x;
	int			y;
	double		wall_top;
	double		wall_bottom;
	int			color_intensity;
	int			color;
}				t_data;

/*RAYCASTING*/
int		keypressed(int key_code, void	*param);
void	update(t_data *data);
int		check_if_wall(t_data *data, double x, double y);

/*RAYCASTING UTILS*/
double	distance_betwn_ab(double x1, double y1, double x2, double y2);
int		chek_if_isleft(t_ray *ray);
int		chek_if_isright(t_ray *ray);
int		chek_if_isup(t_ray *ray);
int		chek_if_isdown(t_ray *ray);
double	get_normalizeangle(double angle);
int		check_if_insidemap(double x, double y, int winwidth, int winheight);
void	create_img(t_data *data, t_img *img, int flag, int i);
void	destroy_and_create_img(t_data *data);
void	generate_new_player_corr(t_data *data, double *new_px, double *new_py);

/*INIT DATA*/
void	init_player(t_data *data);
void	init_window(t_data *data);
int		ft_strlen(char *s);
int		ft_error(char *err);
int		exit_status(int key_code, void	*param);
void	init_ray(t_ray *ray, double rayangle);

/*RENDRING*/
void	rendring_minimap(t_data *data, int x, int y);
void	draw_line(t_data *data, t_point a, t_point b);
int		get_color(t_data *data, int x, int y);
int		ft_rendring(void *param);
void	rendring3dprojectionwalls(t_data *data, t_ray *ray, int stripid);
int		create_rgb(int r, int g, int b);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

/**Pars*/
int		parsing(t_data *data, int ac, char **av);
int		ft_atoi(char *str);
char	**ft_split(char *s, char c);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strdup(char *s1);
char	*get_next_line(int fd);
char	*ft_strchr(char *s, int c);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char *s, unsigned int start, size_t len);

#endif