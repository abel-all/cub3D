/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing___.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychahbi <ychahbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 19:50:48 by ychahbi           #+#    #+#             */
/*   Updated: 2023/08/12 20:02:03 by ychahbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

int	is_digit(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != '\n')
	{
		if (s[i] >= '0' && s[i] <= '9')
			;
		else
			return (0);
		i++;
	}
	return (1);
}

int	not_digi(char *s1, char *s2, char *s3)
{
	if (is_digit(s1) && is_digit(s2) && is_digit(s3))
		return (1);
	return (0);
}

void	check_first_char(char *tmp, int *j)
{
	int	i;

	i = 0;
	*j = 0;
	while (tmp[i] != '\0' || tmp[i] != '\n')
	{
		if (tmp[i] == '1')
			return ;
		else if (tmp[i] == '0' || tmp[i] == 'N'
			|| tmp[i] == 'S' || tmp[i] == 'W' || tmp[i] == 'E')
			ft_error("map error");
		i++;
	}
	while (i >= 0)
	{
		if (tmp[i] == '1')
			return ;
		else if (tmp[i] == '0' || tmp[i] == 'N'
			|| tmp[i] == 'S' || tmp[i] == 'W' || tmp[i] == 'E')
			ft_error("map error");
		i--;
	}
}
