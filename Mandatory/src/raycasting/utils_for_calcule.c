/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_for_calcule.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-all <abel-all@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 13:03:08 by abel-all          #+#    #+#             */
/*   Updated: 2023/07/22 13:14:52 by abel-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

int	ft_strlen(char *s)
{
	int	i;
	
	i = -1;
	while (s[++i])
		;
	return (i);
}

int	ft_error(char *err)
{
	write(2, err, ft_strlen(err));
	exit(EXIT_FAILURE);
}

int	check_if_insidemap(double x, double y, int winwidth, int winheight)
{
    if (x >= 0 && x <= winwidth && y >= 0 && y <= winheight)
		return (1);
	return (0);
}

// void	draw_ray(t_data *data, t_ray *ray, int stripid)
// {
// 	rendring3dprojectionwalls(data, ray, stripid);
// }

double	get_normalizeangle(double angle)
{
	angle = remainder(angle, (2 * M_PI));
	if (angle < 0)
		angle = angle + (2 * M_PI);
	return (angle);
}

int	chek_if_isdown(t_ray *ray)
{
	if (ray->rayangle > 0 && ray->rayangle < M_PI)
		return (1);
	else
		return (0);
}

int	chek_if_isup(t_ray *ray)
{
	return (!chek_if_isdown(ray));
}

int	chek_if_isright(t_ray *ray)
{
	if (ray->rayangle < (0.5 * M_PI) || ray->rayangle > (1.5 * M_PI))
		return (1);
	else
		return (0);
}

int	chek_if_isleft(t_ray *ray)
{
	return (!chek_if_isright(ray));
}

void	init_ray(t_ray *ray, double rayangle)
{
	ray->rayangle = get_normalizeangle(rayangle);
	ray->isdown = chek_if_isdown(ray);
	ray->isup = chek_if_isup(ray);
	ray->isright = chek_if_isright(ray);
	ray->isleft = chek_if_isleft(ray);
	ray->distance = 0;
	ray->horzwallhitx = 0;
	ray->horzwallhity = 0;
	ray->vertwallhitx = 0;
	ray->vertwallhity = 0;
}

double	distance_betwn_ab(double x1, double y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

int	check_if_wall(t_data *data, double x, double y)
{
	int gridx;
	int gridy;

	if (x < 0 || x > WIN_WIDTH || y < 0 || y > WIN_HEIGHT)
		return (1);
	gridx = x / TILE_SIZE;
	gridy = y / TILE_SIZE;
	if (map[gridy][gridx] == 0)
		return (0);
	return (1);
}