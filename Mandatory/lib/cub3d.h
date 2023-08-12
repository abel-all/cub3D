/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychahbi <ychahbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 08:11:17 by abel-all          #+#    #+#             */
/*   Updated: 2023/08/12 09:58:55 by ychahbi          ###   ########.fr       */
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
# include "get_next_line.h"

# define W 13
# define S 1
# define D 2
# define A 0
# define ESC 53
# define KEY_LEFT 123
# define KEY_RIGHT 124

# define TILE_SIZE 20
# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define MINI_WIDTH 200
# define LINE_LENGTH 10
# define PLAYER_HEIGHT 4
# define BORD_HEIGHT 8
# define FOV_ANGLE 1.0471975512
// # define WALL_STRIP_WIDTH 1
# define NUM_OF_RAYS WIN_WIDTH
# define SCALE_FACTOR 0.5
# define MALLOC_ERR "Malloc Error!\n"
# define PARS_ERR "Parsing Error!\n"
# define INIT_ERR "Mlx Init Error!\n"
# define NEW_WIN_ERR "Mlx New Window Error!\n"

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
	double	height;
	int		left_right;
	int		turndirection;
	int		walkdirection;
	double	rotationangle;
	double	movespeed;
	double	rotationspeed;
}				t_player;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct pos_text
{
	int	x1;
	int	x2;
	int	y1;
	int	y2;
}		t_pos;

typedef struct addr
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	unsigned int	*data_addr;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
	int				width;
	int				height;
}					t_addr;

typedef struct s_data
{
	void		*mlx;
	void		*mlx_win;
	double		wall_width;
	double		wall_height;
	double		map_width;
	double		map_height;
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
	int			mouse_x;
	t_player	player;
	t_img		minimap;
	t_img		view;
	t_ray		ray[NUM_OF_RAYS];
	t_point		intersept;
	t_point		step;
	t_point		nexttouch;
	t_point		check;
	t_point		delta;
	int			foundhorzwallhit;
	int			foundvertwallhit;
	double		horzhitdis;
	double		verthitdis;
	double		i;
	double		j;
	double		disprojplane;
	double		wallstripheight;
	double		x;
	double		y;
	double		wall_top;
	double		wall_bottom;
	int			color;
	t_addr		addr_no;
	t_addr		addr_we;
	t_addr		addr_ea;
	t_addr		addr_so;
	t_pos		pos;
}				t_data;

/*RAYCASTING*/
int				keypressed(int key_code, void *param);
void			update(t_data *data);
int				check_if_wall(t_data *data, double x, double y);

/*RAYCASTING UTILS*/
double			distance_betwn_ab(double x1, double y1, double x2, double y2);
int				chek_if_isleft(t_ray *ray);
int				chek_if_isright(t_ray *ray);
int				chek_if_isup(t_ray *ray);
int				chek_if_isdown(t_ray *ray);
double			get_normalizeangle(double angle);
int				check_if_insidemap(double x, double y,
					int winwidth, int winheight);
void			create_img(t_data *data, t_img *img, int flag, int i);
void			destroy_and_create_img(t_data *data);
void			generate_new_player_corr(t_data *data,
					double *new_px, double *new_py);
void			calc_vertintersection(t_data *data, t_ray *ray);
void			calc_horzintersection(t_data *data, t_ray *ray);
void			increment_until_find_wall(t_data *data, t_ray *ray, int f);
void			set_wallhit_corr(t_data *data, t_ray *ray, int f);

/*INIT DATA*/
void			init_player(t_data *data);
void			init_window(t_data *data);
int				ft_strlen(char *s);
int				ft_error(char *err);
int				exit_status(void);
void			init_ray(t_ray *ray, double rayangle);
double			get_rot_angle(t_data *data);

/*RENDRING*/
void			rendring_minimap(t_data *data, int x, int y);
void			draw_line(t_data *data, t_point a, t_point b);
int				get_color(t_data *data, int x, int y);
int				ft_rendring(void *param);
void			rendring3dprojectionwalls(t_data *data,
					t_ray *ray, int stripid);
int				create_rgb(int r, int g, int b);
void			my_mlx_pixel_put(t_img *img, int x, int y, int color);
void			cast_ray(t_data *data, t_ray *ray, double rayangle);

/**Parsing*/
int				parsing(t_data *data, int ac, char **av);
int				ft_atoi(char *str);
char			**ft_split(char *s, char c);
int				ft_strcmp(char *s1, char *s2);
char			*ft_strdup(char *s1);
char			*get_next_line(int fd);
char			*ft_strchr(char *s, int c);
void			*ft_calloc(size_t count, size_t size);
char			*ft_strjoin(char *s1, char *s2);
char			*ft_substr(char *s, int start, int len);
int				allowed(char c, int i);
char			*rm_lin(char *s);
int				empty_line(char	*c);
int				red(t_data *data);
int				check_name(t_data *data, char *name);
int				parsing(t_data *data, int ac, char **av);
int				much_players(t_data *data);
int				check_lines(t_data *data);
int				to_ints(char	**str);
int				check_arg(t_data *data, char	**str);
char			**putmap(t_data *data, char *line);
int				check_zeros(t_data *data);
void			put_spaces(t_data *data);
int				to_end(char *s);
char			*viral(char *tmp, int *i);
char			*ptr(char *s);
int				sp_size(char **str);
int				to_int(char *s);
char			*rm_lin(char *s);
unsigned int	my_mlx_pixel_get(t_addr img, int x, int y);
void			put_data_color(int stripid, t_addr *addr, t_data *data, int x);
void			free_table(char	**ptr);
int				check_if(char	*str);
void			check_emptylines_inmap(t_data *data, char *tmp);
void			free_map_null(t_data *data);
#endif
