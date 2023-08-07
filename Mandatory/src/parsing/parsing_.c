/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychahbi <ychahbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 15:23:22 by abel-all          #+#    #+#             */
/*   Updated: 2023/08/07 20:21:13 by ychahbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"
#include "../../lib/get_next_line.h"

int	much_players(t_data *data)
{
	int	count;
	int	i;
	int	j;

	i = 0;
	count = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'W'
			|| data->map[i][j] == 'E' || data->map[i][j] == 'S')
			{
				data->p_p[0] = j;
				data->p_p[1] = i;
				data->p_r = data->map[i][j];
				count++;
			}
			j++;
		}
		i++;
	}
	return (count);
}

int	check_lines(t_data *data)
{
	int	size;
	int	i;
	int	j;
	int	reut;

	size = sp_size(data->map);
	reut = 1;
	i = 0;
	put_spaces(data);
	while (data->map[i])
	{
		j = 0;
		if (i == 0 || i == size - 1)
			while (data->map[i] && data->map[i][j] != '\0' && reut)
				reut = allowed(data->map[i][j++], i);
		else
			while (data->map[i] && data->map[i][j] != '\n'
			&& data->map[i][j] != '\0' && reut)
				reut = allowed(data->map[i][j++], -1);
		(reut == 0) && (printf("%d %d Error\n", i, j), ft_error(""));
		i++;
	}
	if (check_zeros(data) == 0 || much_players(data) != 1)
		return (ft_error("Error!"), 0);
	return (1);
}

int	to_ints(char	**str)
{
	int	i;

	i = -1;
	if (sp_size(str) != 3)
		return (ft_error("atoi"), -1);
	if (ft_atoi(str[0]) < 0 || ft_atoi(str[0]) > 255)
		return (ft_error("atoi"), -1);
	if (ft_atoi(str[1]) < 0 || ft_atoi(str[1]) > 255)
		return (ft_error("atoi"), -1);
	if (ft_atoi(str[2]) < 0 || ft_atoi(str[2]) > 255)
		return (ft_error("atoi"), -1);
	i = (ft_atoi(str[0]) << 16) | (ft_atoi(str[1]) << 8) | ft_atoi(str[2]);
	return (i);
}

int	check_arg(t_data *data, char	**str)
{
	if (ft_strcmp(str[0], "NO") == 0 || ft_strcmp(str[0], "SO") == 0
		|| ft_strcmp(str[0], "WE") == 0 || ft_strcmp(str[0], "EA") == 0
		|| ft_strcmp(str[0], "F") == 0 || ft_strcmp(str[0], "C") == 0)
	{
		if (ft_strcmp(str[0], "NO") == 0 && data->no == NULL)
			data->no = rm_lin(ft_strdup(str[1]));
		else if (ft_strcmp(str[0], "SO") == 0 && data->so == NULL)
			data->so = rm_lin(ft_strdup(str[1]));
		else if (ft_strcmp(str[0], "WE") == 0 && data->we == NULL)
			data->we = rm_lin(ft_strdup(str[1]));
		else if (ft_strcmp(str[0], "EA") == 0 && data->ea == NULL)
			data->ea = rm_lin(ft_strdup(str[1]));
		else if (ft_strcmp(str[0], "F") == 0 && data->f == -1
			&& to_ints(ft_split(str[1], ',')) != -1)
			data->f = to_ints(ft_split(str[1], ','));
		else if (ft_strcmp(str[0], "C") == 0 && data->c == -1
			&& to_ints(ft_split(str[1], ',')) != -1)
			data->c = to_ints(ft_split(str[1], ','));
		else
			return (ft_error("args"), 0);
		return (1);
	}
	return (ft_error("Some ARgs Not Valid"), 0);
}
