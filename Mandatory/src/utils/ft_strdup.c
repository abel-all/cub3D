/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychahbi <ychahbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 09:46:37 by ychahbi           #+#    #+#             */
/*   Updated: 2023/08/10 16:34:13 by ychahbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

char	*ft_strdup(char *s1)
{
	char	*ptr;
	int		dex;

	ptr = (char *)malloc((ft_strlen(s1) + 1));
	if (!ptr)
		return (NULL);
	else
	{
		dex = 0;
		while (s1[dex] != '\0')
		{
			ptr[dex] = s1[dex];
			dex++;
		}
		ptr[dex] = '\0';
	}
	return (ptr);
}
