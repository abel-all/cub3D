/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing__.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-all <abel-all@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 15:24:47 by abel-all          #+#    #+#             */
/*   Updated: 2023/08/06 15:40:19 by abel-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"
#include "../../lib/get_next_line.h"

char	**putmap(t_data *data, char *line)
{
	char	**new;
	int		i;
	int		size;

	i = 0;
	if (ft_strlen(line) > data->l_line)
		data->l_line = ft_strlen(line);
	size = sp_size(data->map);
	new = NULL;
	if (data->map == NULL)
	{
		new = malloc(sizeof(char *) * 2);
		new[0] = rm_lin(line);
		new[1] = NULL;
	}
	else
	{
		new = malloc(sizeof(char *) * (size + 2));
		while (i < size)
		{
			new[i] = rm_lin(data->map[i]);
			i++;
		}
		new[i++] = rm_lin(line);
		new[i] = NULL;
	}
	return (new);
}

int	allowed(char c, int i)
{
	if (i == -2 && (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W'))
		return (2);
	else if (i == -1 && (c == '0' || c == '1' \
	|| c == ' ' || c == 'N' || c == 'S' || c == 'E' || c == 'W'))
		return (1);
	else if (i == 0 && (c == '1' || c == ' '))
		return (1);
	else if (i != -1 && i != 0 && (c == '1' || c == ' '))
		return (1);
	return (0);
}

int	check_zeros(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j] != '\0')
		{
			if (data->map[i][j] == '0')
			{
				if (data->map[i + 1][j] == ' ' || data->map[i - 1][j] == ' '
					|| data->map[i][j + 1] == ' ' || data->map[i][j - 1] == ' ')
					return (printf("%d %d Ok Error\n", i, j), 0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

void	put_spaces(t_data *data)
{
	int		i;
	int		j;
	char	*map;

	i = 0;
	map = malloc(sizeof(char) * (data->l_line + 1));
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j] != '\n' && data->map[i][j] != '\0')
		{
			map[j] = data->map[i][j];
			j++;
		}
		while (j < data->l_line)
			map[j++] = ' ';
		map[j] = '\0';
		data->map[i++] = ft_strdup(map);
	}
	data->map_width = TILE_SIZE * (data->l_line - 1);
	data->map_height = TILE_SIZE * i;
}
