/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-all <abel-all@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 12:37:20 by abel-all          #+#    #+#             */
/*   Updated: 2023/08/13 08:56:56 by abel-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/cub3d.h"

void	red_textures(t_data *data)
{
	data->addr_no.img_ptr = mlx_xpm_file_to_image(data->mlx, data->no,
			&data->addr_no.width, &data->addr_no.height);
	data->addr_we.img_ptr = mlx_xpm_file_to_image(data->mlx, data->we,
			&data->addr_we.width, &data->addr_we.height);
	data->addr_ea.img_ptr = mlx_xpm_file_to_image(data->mlx, data->ea,
			&data->addr_ea.width, &data->addr_ea.height);
	data->addr_so.img_ptr = mlx_xpm_file_to_image(data->mlx, data->so,
			&data->addr_so.width, &data->addr_so.height);
	if (!data->addr_no.img_ptr || !data->addr_we.img_ptr
		|| !data->addr_ea.img_ptr || !data->addr_so.img_ptr)
		ft_error("can't open Textures");
	data->addr_no.data_addr = (unsigned int *)mlx_get_data_addr(
			data->addr_no.img_ptr, &data->addr_no.bits_per_pixel,
			&data->addr_no.size_line, &data->addr_no.endian);
	data->addr_we.data_addr = (unsigned int *)mlx_get_data_addr(
			data->addr_we.img_ptr, &data->addr_we.bits_per_pixel,
			&data->addr_we.size_line, &data->addr_we.endian);
	data->addr_ea.data_addr = (unsigned int *)mlx_get_data_addr(
			data->addr_ea.img_ptr, &data->addr_ea.bits_per_pixel,
			&data->addr_ea.size_line, &data->addr_ea.endian);
	data->addr_so.data_addr = (unsigned int *)mlx_get_data_addr(
			data->addr_so.img_ptr, &data->addr_so.bits_per_pixel,
			&data->addr_so.size_line, &data->addr_so.endian);
}

int	mouse_move(int x, int y, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (x > 0 && x < WIN_WIDTH && y > 0 && y < WIN_HEIGHT)
	{
		if (x > data->mouse_x)
			data->player.turndirection = 1;
		else
			data->player.turndirection = -1;
		update(data);
		data->mouse_x = x;
	}
	return (0);
}

int	keyrelease(int key, t_data *data)
{
	if (key == KEY_RIGHT)
		data->player.turndirection = 0;
	else if (key == KEY_LEFT)
		data->player.turndirection = 0;
	else if (key == W)
		data->player.walkdirection = 0;
	else if (key == S)
		data->player.walkdirection = 0;
	else if (key == A)
		data->player.left_right = 0;
	else if (key == D)
		data->player.left_right = 0;
	else
		return (0);
	update(data);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = ft_malloc(sizeof(t_data));
	parsing(data, ac, av);
	init_window(data);
	init_player(data);
	red_textures(data);
	update(data);
	ft_rendring(data);
	mlx_hook(data->mlx_win, 2, 0, keypressed, data);
	mlx_hook(data->mlx_win, 3, 0, keyrelease, data);
	mlx_hook(data->mlx_win, 17, 0, exit_status, data);
	mlx_hook(data->mlx_win, 6, 0, mouse_move, data);
	mlx_loop_hook(data->mlx, ft_rendring, data);
	mlx_loop(data->mlx);
}
