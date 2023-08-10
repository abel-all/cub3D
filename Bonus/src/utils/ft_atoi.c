/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychahbi <ychahbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 00:25:06 by ychahbi           #+#    #+#             */
/*   Updated: 2023/08/10 18:04:21 by ychahbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

int	ft_strlen(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		;
	return (i);
}

char	*rm_lin(char *s)
{
	int		i;
	char	*ret;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			s[i] = '\0';
		i++;
	}
	ret = ft_strdup(s);
	return (free(s), ret);
}

int	ft_error(char *err)
{
	write(2, err, ft_strlen(err));
	exit(EXIT_FAILURE);
}

int	ft_atoi(char *str)
{
	int	dex;
	int	sign;
	int	rslt;

	dex = 0;
	sign = 1;
	rslt = 0;
	while ((str[dex] >= 9 && str[dex] <= 13)
		|| str[dex] == 32)
		dex++;
	if (str[dex] == '-' || str[dex] == '+')
	{
		if (str[dex] == '-')
		{
			sign = sign * -1;
		}
		dex++;
	}
	while (str[dex] >= '0' && str[dex] <= '9')
	{
		rslt = (rslt * 10) + (str[dex] - 48);
		dex++;
	}
	return (rslt * sign);
}
