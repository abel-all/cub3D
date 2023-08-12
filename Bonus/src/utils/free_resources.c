/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-all <abel-all@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 13:12:13 by abel-all          #+#    #+#             */
/*   Updated: 2023/08/12 13:12:48 by abel-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

static void	free_2d_tab(char **ptr, int i)
{
	while (ptr[++i])
		free(ptr[i]);
	free(ptr);
}

static void	free_t_addr(t_addr addr)
{
	free(addr.mlx_ptr);
	free(addr.win_ptr);
	free(addr.img_ptr);
	free(addr.data_addr);
}

int	free_resources(t_data *data)
{
	free_2d_tab(data->map, -1);
	free(data->no);
	free(data->so);
	free(data->we);
	free(data->ea);
	mlx_destroy_window(data->mlx, data->mlx_win);
	mlx_destroy_image(data->mlx, data->minimap.img);
	mlx_destroy_image(data->mlx, data->view.img);
	free(data->mlx);
	free_t_addr(data->addr_ea);
	free_t_addr(data->addr_we);
	free_t_addr(data->addr_so);
	free_t_addr(data->addr_no);
	free(data);
	return (EXIT_FAILURE);
}
