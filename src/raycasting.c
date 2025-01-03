/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:46:05 by dbejar-s          #+#    #+#             */
/*   Updated: 2024/12/27 21:17:01 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

/**
 * Draws the wall textures.
 * 
 * @param m Pointer to the macro structure containing map and ray information.
 * @param top_wall The top coordinate of the wall.
 * @param bottom The bottom coordinate of the wall.
 * @param wall_h The height of the wall.
 */
void	draw_wall(t_macro *m, int top_wall, int bottom, double wall_h)
{
	double			x_offset;
	double			y_offset;
	mlx_texture_t	*tex;
	uint32_t		*arr;
	double			factor;

	tex = get_texture(m, m->ray->hit);
	arr = (uint32_t *)tex->pixels;
	factor = (double)tex->height / wall_h;
	x_offset = x_off(tex, m);
	y_offset = (top_wall - (m->height / 2) + (wall_h / 2)) * factor;
	if (y_offset < 0)
		y_offset = 0;
	while (top_wall < bottom)
	{
		if (m->ray->index >= 0 && m->ray->index < m->width && top_wall >= 0
			&& top_wall < m->height)
			mlx_put_pixel(m->scene_i, m->ray->index, top_wall++,
				make_color(arr[(int)y_offset * tex->width + (int)x_offset]));
		y_offset += factor;
	}
}

/**
 * Paints the floor on the screen using vertical lines
 * 
 * @param m Pointer to the macro structure containing map and ray information.
 * @param vertical The vertical coordinate.
 * @param i The starting coordinate for painting.
 */
static void	paint_floor(t_macro *m, int vertical, int i)
{
	while (i < m->height)
	{
		if (vertical >= 0 && vertical < m->width && i >= 0 && i < m->height)
			mlx_put_pixel(m->scene_i, vertical, i++, m->ray->floor);
	}
}

/**
 * Calculates the wall size and call the function to draw textures on them
 * 
 * @param m Pointer to the macro structure containing map and ray information.
 * @param vertical The vertical coordinate.
 */
void	do_wall(t_macro *m, int vertical)
{
	double	wall_h;
	double	bottom;
	double	top_wall;
	int		i;

	m->ray->distance *= cos(normalize(m->ray->ray_angle - m->ray->play_angle));
	wall_h = (BLOCK / m->ray->distance) * ((m->width / 2)) / 2;
	wall_h /= (sin(m->ray->play_view / 2) / cos(m->ray->play_view / 2));
	top_wall = (m->height / 2) - (wall_h);
	bottom = (m->height / 2) + (wall_h);
	if (bottom > m->height)
		bottom = m->height;
	if (top_wall < 0)
		top_wall = 0;
	m->ray->index = vertical;
	i = 0;
	while (i <= m->height / 2)
	{
		if (vertical >= 0 && vertical < m->width && i >= 0 && i < m->height)
			mlx_put_pixel(m->scene_i, vertical, i++, m->ray->ceiling);
	}
	paint_floor(m, vertical, i);
	draw_wall(m, top_wall, bottom, 2 * wall_h);
}

/**
 * Performs the raycasting algorithm to render the 3D view.
 * Based on DDA algorithm.
 * 
 * @param m Pointer to the macro structure containing map and ray information.
 */
void	raycast(t_macro *m)
{
	double	x_cross;
	double	y_cross;
	int		vertical;
	double	dda;

	vertical = 0;
	dda = 0;
	m->ray->ray_angle = m->ray->play_angle - (m->ray->play_view / 2);
	while (vertical < m->width)
	{
		m->ray->hit = 0;
		x_cross = x_dda(m, fmod(m->ray->ray_angle, 2 * M_PI), dda);
		y_cross = y_dda(m, fmod(m->ray->ray_angle, 2 * M_PI), dda);
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
