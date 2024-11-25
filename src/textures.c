/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbejar-s <dbejar-s@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 23:00:35 by dbejar-s          #+#    #+#             */
/*   Updated: 2024/11/25 23:47:14 by dbejar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

float	x_dda(t_macro *m, double angle)
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
	h_x = m->ray->pos_pl_x + (h_y - m->ray->pos_pl_y)
		/ (sin(angle) / cos(angle));
	if ((radian_side(angle, 0) && x_step > 0)
		|| (!radian_side(angle, 0) && x_step < 0))
		x_step *= -1;
	while (wall_hit(h_x, h_y - pixel, m))
	{
		h_x += x_step;
		h_y += y_step;
	}
	m->ray->ray_dir_hx = h_x;
	m->ray->ray_dir_hy = h_y;
	return (sqrt(pow(h_x - m->ray->pos_pl_x, 2)
			+ pow(h_y - m->ray->pos_pl_y, 2)));
}

float	y_dda(t_macro *m, double angle)
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
	v_y = m->ray->pos_pl_y + (v_x - m->ray->pos_pl_x)
		* (sin(angle) / cos(angle));
	if ((radian_side(angle, 1) && y_step < 0)
		|| (!radian_side(angle, 1) && y_step > 0))
		y_step *= -1;
	while (wall_hit(v_x - pixel, v_y, m))
	{
		v_x += x_step;
		v_y += y_step;
	}
	m->ray->ray_dir_vx = v_x;
	m->ray->ray_dir_vy = v_y;
	return (sqrt(pow(v_x - m->ray->pos_pl_x, 2)
			+ pow(v_y - m->ray->pos_pl_y, 2)));
}

float	nor_angle(float angle)
{
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}

mlx_texture_t	*get_texture(t_macro *m, int flag)
{
	m->ray->ray_angle = nor_angle(m->ray->ray_angle);
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

double	get_x_o(mlx_texture_t	*texture, t_macro *m)
{
	double	x_o;

	if (m->ray->hit == 1)
		x_o = (int)fmodf((m->ray->ray_dir_hx
					* (texture->width / BLOCK)), texture->width);
	else
		x_o = (int)fmodf((m->ray->ray_dir_vy
					* (texture->width / BLOCK)), texture->width);
	return (x_o);
}