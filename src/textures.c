/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 23:00:35 by dbejar-s          #+#    #+#             */
/*   Updated: 2024/12/27 21:17:01 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * Calculates the distance to the nearest horizontal wall hit using DDA.
 * 
 * @param m Pointer to the macro structure containing ray information.
 * @param angle The angle of the ray.
 * @param dda The initial DDA value.
 * @return The distance to the nearest horizontal wall hit.
 */
float	x_dda(t_macro *m, double angle, double dda)
{
	float	h_x;
	float	h_y;
	float	x_step;
	float	y_step;
	int		pixel;

	y_step = BLOCK;
	x_step = BLOCK / (sin(angle) / cos(angle));
	h_y = floor(m->ray->pos_pl_y / BLOCK) * BLOCK;
	pixel = cross_lines(angle, &h_y, &y_step, 1);
	h_x = m->ray->pos_pl_x + (h_y - m->ray->pos_pl_y) / (sin(angle)
			/ cos(angle));
	if ((radian_side(angle, 0) && x_step > 0) || (!radian_side(angle, 0)
			&& x_step < 0))
		x_step *= -1;
	while (wall_hit(h_x, h_y - pixel, m))
	{
		h_x += x_step;
		h_y += y_step;
	}
	m->ray->ray_dir_hx = h_x;
	m->ray->ray_dir_hy = h_y;
	dda = hypot(h_x - m->ray->pos_pl_x, h_y - m->ray->pos_pl_y);
	return (dda);
}

/**
 * Calculates the distance to the nearest vertical wall hit using DDA.
 * 
 * @param m Pointer to the macro structure containing ray information.
 * @param angle The angle of the ray.
 * @param dda The initial DDA value.
 * @return The distance to the nearest vertical wall hit.
 */
float	y_dda(t_macro *m, double angle, double dda)
{
	float	v_x;
	float	v_y;
	float	x_step;
	float	y_step;
	int		pixel;

	x_step = BLOCK;
	y_step = BLOCK * (sin(angle) / cos(angle));
	v_x = floor(m->ray->pos_pl_x / BLOCK) * BLOCK;
	pixel = cross_lines(angle, &v_x, &x_step, 0);
	v_y = m->ray->pos_pl_y;
	v_y += (v_x - m->ray->pos_pl_x) * (sin(angle) / cos(angle));
	if ((radian_side(angle, 1) && y_step < 0) || (!radian_side(angle, 1)
			&& y_step > 0))
		y_step *= -1;
	while (wall_hit(v_x - pixel, v_y, m))
	{
		v_x += x_step;
		v_y += y_step;
	}
	m->ray->ray_dir_vx = v_x;
	m->ray->ray_dir_vy = v_y;
	dda = hypot(v_x - m->ray->pos_pl_x, v_y - m->ray->pos_pl_y);
	return (dda);
}

/**
 * Normalizes the given angle to the range [0, 2*PI].
 * 
 * @param angle The angle to normalize.
 * @return The normalized angle.
 */
float	normalize(float angle)
{
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}

/**
 * Retrieves the texture based on the hit direction.
 * 
 * @param m Pointer to the macro structure containing texture information.
 * @param flag The hit direction (1 for north/south, 0 for east/west).
 * @return A pointer to the corresponding texture.
 */
mlx_texture_t	*get_texture(t_macro *m, int flag)
{
	m->ray->ray_angle = normalize(m->ray->ray_angle);
	if (flag == 0)
	{
		if (m->ray->ray_angle > M_PI / 2 && m->ray->ray_angle < 3 * (M_PI / 2))
			return (m->tex->ea);
		else
			return (m->tex->we);
	}
	else
	{
		if (m->ray->ray_angle > 0 && m->ray->ray_angle < M_PI)
			return (m->tex->no);
		else
			return (m->tex->so);
	}
}

/**
 * Calculates the x-offset for the texture mapping.
 * 
 * @param texture Pointer to the texture.
 * @param m Pointer to the macro structure containing ray information.
 * @return The x-offset for the texture mapping.
 */
double	x_off(mlx_texture_t *texture, t_macro *m)
{
	double	x_offset;
	float	horizontal;
	float	vertical;

	horizontal = (m->ray->ray_dir_hx * (texture->width / BLOCK));
	vertical = (m->ray->ray_dir_vy * (texture->width / BLOCK));
	if (m->ray->hit == 1)
		x_offset = (int)fmodf(horizontal, texture->width);
	else
		x_offset = (int)fmodf(vertical, texture->width);
	return (x_offset);
}
