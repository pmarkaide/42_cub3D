/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raying.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 23:30:02 by dbejar-s          #+#    #+#             */
/*   Updated: 2024/11/19 13:14:50 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	draw_wall(t_macro *m, int top_wall, int bottom, double wall_h)
{
	double			x_o;
	double			y_o;
	mlx_texture_t	*texture;
	uint32_t		*arr;
	double			factor;

	texture = get_texture(m, m->ray->hit);
	arr = (uint32_t *)texture->pixels;
	factor = (double)texture->height / wall_h;
	x_o = get_x_o(texture, m);
	y_o = (top_wall - (m->height / 2) + (wall_h / 2)) * factor;
	if (y_o < 0)
		y_o = 0;
	while (top_wall < bottom)
	{
		if (m->ray->index >= 0 && m->ray->index < m->width
			&& top_wall >= 0 && top_wall < m->height)
			mlx_put_pixel(m->images->scene_i, m->ray->index, top_wall++,
				make_color(arr[(int)y_o * texture->width + (int)x_o]));
		y_o += factor;
	}
}

void	paint_background(t_macro *m, int ray)
{
	int		i;

	i = m->height / 2;
	while (i < m->height)
	{
		if (ray >= 0 && ray < m->width && i >= 0 && i < m->height)
			mlx_put_pixel(m->images->scene_i, ray, i++, m->ray->floor);
	}
	i = 0;
	while (i <= m->height / 2)
	{
		if (ray >= 0 && ray < m->width && i >= 0 && i < m->height)
			mlx_put_pixel(m->images->scene_i, ray, i++, m->ray->ceiling);
	}
}

void	do_wall(t_macro *m, int vertical)
{
	double	wall_h;
	double	bottom;
	double	top_wall;

	m->ray->distance *= cos(nor_angle(m->ray->ray_angle - m->ray->play_angle));
	wall_h = (BLOCK / m->ray->distance) * ((m->width / 2));
	wall_h /= tan(m->ray->play_view / 2);
	bottom = (m->height / 2) + (wall_h / 2);
	top_wall = (m->height / 2) - (wall_h / 2);
	if (bottom > m->height)
		bottom = m->height;
	if (top_wall < 0)
		top_wall = 0;
	m->ray->index = vertical;
	paint_background(m, vertical);
	draw_wall(m, top_wall, bottom, wall_h);
}

void	raycast(t_macro *m)
{
	double	x_cross;
	double	y_cross;
	int		vertical;

	vertical = 0;
	m->ray->ray_angle = m->ray->play_angle - (m->ray->play_view / 2);
	while (vertical < m->width)
	{
		m->ray->hit = 0;
		x_cross = x_dda(m, fmod(m->ray->ray_angle, 2 * M_PI));
		y_cross = y_dda(m, fmod(m->ray->ray_angle, 2 * M_PI));
		if (x_cross < y_cross)
		{
			m->ray->distance = x_cross;
			m->ray->hit = 1;
		}
		else
			m->ray->distance = y_cross;
		do_wall(m, vertical);
		vertical++;
		m->ray->ray_angle += m->ray->play_view / m->width;
	}
}
