/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 23:01:59 by dbejar-s          #+#    #+#             */
/*   Updated: 2024/12/27 21:11:36 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * Converts an integer color value to a different format.
 * 
 * @param color The integer representing the color.
 * @return The converted color value.
 */
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

/**
 * Determines the side of the angle in radians.
 * 
 * @param angle The angle in radians.
 * @param side The side to check (0 for vertical, 1 for horizontal).
 * @return 1 if the angle is on the specified side, 0 otherwise.
 */
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

/**
 * Calculates the crossing lines for the DDA algorithm.
 * 
 * @param angle The angle in radians.
 * @param crossed Pointer to the crossed value.
 * @param step Pointer to the step value.
 * @param x_dda Flag indicating if the DDA is for the x-axis.
 * @return The direction of the crossing line.
 */
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

/**
 * Checks if a wall is hit at the specified block coordinates.
 * 
 * @param x_block The x-coordinate of the block.
 * @param y_block The y-coordinate of the block.
 * @param m Pointer to the macro structure containing map information.
 * @return 1 if a wall is hit, 0 otherwise.
 */
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
	if ((y >= m->map->h_buff || x >= m->map->w_buff))
		return (0);
	limit = (int)ft_strlen(m->map->buff[y]);
	if (m->map->buff[y] && x <= limit && m->map->buff[y][x] == '1')
		return (0);
	return (1);
}
