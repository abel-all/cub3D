/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-all <abel-all@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 01:38:15 by ychahbi           #+#    #+#             */
/*   Updated: 2023/08/06 15:32:04 by abel-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"
#include "../../lib/get_next_line.h"

char	*rm_lin(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			s[i] = '\0';
		i++;
	}
	return (s);
}

int	empty_line(char	*c)
{
	int	i;

	i = 0;
	while (c[i] != '\0' && c[i] != '\n')
	{
		if (c[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	red(t_data *data)
{
	int		fd;
	char	*tmp;
	int		i;
	int		j;

	i = 1;
	fd = open(data->mapname, O_RDONLY, 0666);
	tmp = get_next_line(fd);
	while (tmp)
	{
		if (i <= 6)
		{
			if (sp_size(ft_split(tmp, 32)) == 2 && check_arg(data, \
			ft_split(tmp, 32)))
				i++;
			else if (empty_line(tmp))
				;
			else
				return (puts("args - Error! - 0"), -1);
		}
		else
		{
			j = 0;
			while (tmp[j] != '\0' && tmp[j] != '\n')
				if (!allowed(tmp[j++], -1))
					return (puts("Map parsing"), -1);
			if (j)
				data->map = putmap(data, tmp);
		}
		tmp = get_next_line(fd);
	}
	if (check_lines(data) != 1)
		return (-1);
	return (0);
}

int	check_name(t_data *data, char *name)
{
	int	fd;
	int	len;

	len = ft_strlen(name);
	if (ft_strcmp(*(&name) + (len - ft_strlen(".cub")), ".cub"))
		return (printf("Map name Error -> "), -1);
	if (open (name, O_RDONLY, 0666) == -1)
		return (close (fd), printf("can't open file -> "), -1);
	data->mapname = name;
	return (close (fd), 0);
}

int	parsing(t_data *data, int ac, char **av)
{
	data->map = NULL;
	data->no = NULL;
	data->so = NULL;
	data->we = NULL;
	data->ea = NULL;
	data->c = -1;
	data->f = -1;
	if (ac == 2 && check_name(data, av[1]) == 0 && red(data) == 0)
		return (1);
	else
		return (printf("Parsing Error!"), -1);
}
