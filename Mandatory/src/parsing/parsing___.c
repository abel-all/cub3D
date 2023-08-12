/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing___.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychahbi <ychahbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 15:25:59 by abel-all          #+#    #+#             */
/*   Updated: 2023/08/12 19:50:56 by ychahbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

int	sp_size(char **str)
{
	int	i;

	i = 0;
	while (str && str[i] != NULL)
		i++;
	return (i);
}

void	check_emptylines_inmap(t_data *data, char *tmp)
{
	if (sp_size(data->map) != 0)
		ft_error("ERROR");
	free(tmp);
}

void	free_map_null(t_data *data)
{
	free_table(data->map);
	data->map = NULL;
}

void	free_table(char	**ptr)
{
	int	i;

	i = 0;
	while (ptr && ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

int	to_int(char	*s)
{
	int		i;
	int		j;
	char	**str;

	i = 0;
	j = 0;
	str = NULL;
	str = ft_split(s, 32);
	if (sp_size(str) == 2)
	{
		free_table(str);
		str = ft_split(s, ',');
		if (sp_size(str) == 3)
			i = (ft_atoi(str[0]) << 16) | \
			(ft_atoi(str[1]) << 8) | ft_atoi(str[2]);
		else
			return (-1);
	}
	else
		return (-1);
	free_table(str);
	return (i);
}
