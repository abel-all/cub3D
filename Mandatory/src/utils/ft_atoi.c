/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychahbi <ychahbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 00:25:06 by ychahbi           #+#    #+#             */
/*   Updated: 2023/07/29 21:15:21 by ychahbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

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
