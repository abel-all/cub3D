/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-all <abel-all@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 01:38:15 by ychahbi           #+#    #+#             */
/*   Updated: 2023/08/05 16:54:43 by abel-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"
#include "../../lib/get_next_line.h"
#include <stdio.h>


int	to_end(char *s)
{
	int	i;

	i = 0;
	while (s[i] == 32)
		i++;
	i = 0;
	while (s[i] != '\0' && s[i] != '\n' && s[i] != 32)
		i++;
	return (i);
}

char	*viral(char *tmp, int *i)
{
	int		j;
	char	*file;

	*i = *i + 2;
	j = 0;
	while (tmp[*i] == 32)
		(*i)++;
	file = malloc(sizeof(char) * (to_end((&(tmp[*i]))) + 1));
	while (tmp[*i] != '\0' && tmp[*i] != '\n' && tmp[*i] != 32)
		file[j++] = tmp[(*i)++];
	file[j] = '\0';
	return (file);
}

char	*ptr(char *s)
{
	int		len;
	char	*ptr;
	int		i;

	ptr = malloc((sizeof(char) * len) + 1);
	i = -1;
	len = ft_strlen(s);
	while (++i <= len)
		ptr[i] = s[i];
	ptr[i] = '\0';
	return (ptr);
}

int	sp_size(char **str)
{
	int	i;

	i = 0;
	while (str && str[i] != NULL)
		i++;
	return (i);
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
		str = ft_split(s, ',');
		if (sp_size(str) == 3)
			i = (ft_atoi(str[0]) << 16) | (ft_atoi(str[1]) << 8) | ft_atoi(str[2]);
		else
			return (-1);
	}
	else
		return (-1);
	return (i);
}

char	*rm_lin(char	*s)
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
		new = malloc(sizeof(char *) + 1);
		new[0] = rm_lin(line);
		new[1] = NULL;
	}
	else
	{
		new = malloc(sizeof(char*) * (size + 2));
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
	if (i == -1 && (c == '0' || c == '1'
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
	map = malloc(sizeof(char) * data->l_line);
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
	i = 0;
	put_spaces(data);
	while (data->map[i])
	{
		j = 0;
		if (i == 0 || i == size - 1)	
			while (data->map[i] && data->map[i][j] != '\0' && (reut = allowed(data->map[i][j++], i)));
		else
			while (data->map[i] && data->map[i][j] != '\n'
				&& data->map[i][j] != '\0' && (reut = allowed(data->map[i][j++], -1)));
		if (reut == 0)
			return (printf("%d %d Ok Error\n", i, j), 0);
		i++;
	}
	if (check_zeros(data) == 0 || much_players(data) != 1)
		return (puts("Error!"), 0);
	return (1);
}

int	to_ints(char	**str)
{
	int	i;

	i = -1;
	if (sp_size(str) != 3)
		return (puts("atoi"), -1);
	if (ft_atoi(str[0]) < 0 || ft_atoi(str[0]) > 255)
		return (puts("atoi"), -1);
	if (ft_atoi(str[1]) < 0 || ft_atoi(str[1]) > 255)
		return (puts("atoi"), -1);
	if (ft_atoi(str[2]) < 0 || ft_atoi(str[2]) > 255)
		return (puts("atoi"), -1);
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
			data->no = ft_strdup(str[1]);
		else if (ft_strcmp(str[0], "SO") == 0 && data->so == NULL)
			data->so = ft_strdup(str[1]);
		else if (ft_strcmp(str[0], "WE") == 0 && data->we == NULL)
			data->we = ft_strdup(str[1]);
		else if (ft_strcmp(str[0], "EA") == 0 && data->ea == NULL)
			data->ea = ft_strdup(str[1]);
		else if (ft_strcmp(str[0], "F") == 0 && data->f == -1
			&& to_ints(ft_split(str[1], ',')) != -1)
			data->f = to_ints(ft_split(str[1], ','));
		else if (ft_strcmp(str[0], "C") == 0 && data->c == -1
			&& to_ints(ft_split(str[1], ',')) != -1)
			data->c = to_ints(ft_split(str[1], ','));
		else
			return (puts("args"), 0);
		return (1);
	}
	return (puts("test"), 0);
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
			if (sp_size(ft_split(tmp, 32)) == 2 && check_arg(data, ft_split(tmp, 32)))
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
