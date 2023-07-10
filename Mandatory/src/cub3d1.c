/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-all <abel-all@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 12:37:20 by abel-all          #+#    #+#             */
/*   Updated: 2023/07/10 07:51:25 by abel-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rendring(t_data *data, t_player *player)
{
	draw_2d_map(data);// rendri
	draw_player(data, player, 0, 0);
}

int main()
{
	t_data	    *data;
	t_player	*player;
	t_img		*img;

	data = malloc(sizeof(t_data));
	player = malloc(sizeof(t_player));
	if (!data)
		ft_error(MALLOC_ERR);
    init_window(data, player);// is setup part
	rendring(data, player);// rendring map and player
	mlx_key_hook(data->mlx_win, keys_handler, data);
	mlx_loop(data->mlx);
}