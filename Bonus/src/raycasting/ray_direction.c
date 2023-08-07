/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_direction.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-all <abel-all@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 14:29:01 by abel-all          #+#    #+#             */
/*   Updated: 2023/08/06 14:29:17 by abel-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

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

double	distance_betwn_ab(double x1, double y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}
