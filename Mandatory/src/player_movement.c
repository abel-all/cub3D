/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-all <abel-all@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 15:58:23 by abel-all          #+#    #+#             */
/*   Updated: 2023/07/11 10:46:45 by abel-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/cub3d.h"

int keys_handler(int key_code, void *param)
{
    t_data  *data;

    data = (t_data*)param;
    if (key_code == W)
    {
        data->player->y--;
        draw_player(data, data->player, 0, 0);
    }
    if (key_code == S)
    {
        data->player->y++;
        draw_player(data, data->player, 0, 0);
    }
    if (key_code == A)
    {
        data->player->x--;
        draw_player(data, data->player, 0, 0);
    }
    if (key_code == D)
    {
        data->player->x++;
        draw_player(data, data->player, 0, 0);
    }
    if (key_code == ESC)
        exit(EXIT_FAILURE);
    return 0;
}