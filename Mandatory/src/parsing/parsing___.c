/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing___.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-all <abel-all@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 15:25:59 by abel-all          #+#    #+#             */
/*   Updated: 2023/08/06 15:26:09 by abel-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"
#include "../../lib/get_next_line.h"

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
			i = (ft_atoi(str[0]) << 16) | \
			(ft_atoi(str[1]) << 8) | ft_atoi(str[2]);
		else
			return (-1);
	}
	else
		return (-1);
	return (i);
}
