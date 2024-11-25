/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbejar-s <dbejar-s@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 23:01:59 by dbejar-s          #+#    #+#             */
/*   Updated: 2024/11/25 23:02:10 by dbejar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	reverse_bytes(int c)
{
	unsigned int	b;

	b = 0;
	b |= (c & 0xFF) << 24;
	b |= (c & 0xFF00) << 8;
	b |= (c & 0xFF0000) >> 8;
	b |= (c & 0xFF000000) >> 24;
	return (b);
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

int	wall_hit(float x, float y, t_macro *m)
{
	int		x_m;
	int		y_m;

	if (x < 0 || y < 0)
		return (0);
	x_m = floor (x / BLOCK);
	y_m = floor (y / BLOCK);
	if ((y_m >= m->map->h_map || x_m >= m->map->w_map))
		return (0);
	if (m->map->grid[y_m] && x_m <= (int)ft_strlen(m->map->grid[y_m]))
		if (m->map->grid[y_m][x_m] == '1')
			return (0);
	return (1);
}