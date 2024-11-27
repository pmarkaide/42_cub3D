/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbejar-s <dbejar-s@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 23:01:59 by dbejar-s          #+#    #+#             */
/*   Updated: 2024/11/27 09:33:35 by dbejar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	make_color(int color)
{
	unsigned char	bytes[4];
	unsigned int	res;

	bytes[0] = (color >> 24) & 0xFF;
	bytes[1] = (color >> 16) & 0xFF;
	bytes[2] = (color >> 8) & 0xFF;
	bytes[3] = color & 0xFF;
	res = (bytes[3] << 24) | (bytes[2] << 16) | (bytes[1] << 8) | bytes[0];
	return (res);
}

int	radian_side(double angle, int side)
{
	if (side)
	{
		if (angle > 0 && angle < M_PI)
			return (1);
	}
	else if (!side)
	{
		if (angle > (M_PI / 2) && angle < (3 * M_PI) / 2)
			return (1);
	}
	return (0);
}

int	cross_lines(double angle, float *crossed, float *step, int x_dda)
{
	if (x_dda)
	{
		if (angle > 0 && angle < M_PI)
		{
			*crossed += BLOCK;
			return (-1);
		}
		*step *= -1;
		return (1);
	}
	if (!(angle > M_PI / 2 && angle < 3 * M_PI / 2))
	{
		*crossed += BLOCK;
		return (-1);
	}
	*step *= -1;
	return (1);
}

int	wall_hit(float x_block, float y_block, t_macro *m)
{
	int	x;
	int	y;
	int	limit;

	limit = 0;
	if (x_block < 0 || y_block < 0)
		return (0);
	x = floor(x_block / BLOCK);
	y = floor(y_block / BLOCK);
	if ((y >= m->map->h_buff || x >= m->map->w_map))
		return (0);
	limit = (int)ft_strlen(m->map->buff[y]);
	if (m->map->buff[y] && x <= limit && m->map->buff[y][x] == '1')
		return (0);
	return (1);
}
