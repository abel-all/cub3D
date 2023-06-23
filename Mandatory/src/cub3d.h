/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-all <abel-all@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 08:11:17 by abel-all          #+#    #+#             */
/*   Updated: 2023/06/22 16:04:34 by abel-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <mlx.h>

#define TILE_SIZE 50
#define MAP_NUM_ROWS 10
#define MAP_NUM_COLS 14
#define WIN_WIDTH (MAP_NUM_COLS * TILE_SIZE) 
#define WIN_HEIGHT (MAP_NUM_ROWS * TILE_SIZE)

typedef struct s_data
{
	void	*mlx;
	void	*mlx_win;
}				t_data;

#endif