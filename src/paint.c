/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 23:26:44 by dbejar-s          #+#    #+#             */
/*   Updated: 2024/11/19 14:57:15 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	calculate_wall_distance(t_macro *m)
{
	if (m->ray->side == 0)
		m->ray->perp_wall_dist = (m->ray->map_x - m->ray->pos_pl_x / BLOCK + (1
					- m->ray->step_x) / 2) / m->ray->ray_dir_x;
	else
		m->ray->perp_wall_dist = (m->ray->map_y - m->ray->pos_pl_y / BLOCK + (1
					- m->ray->step_y) / 2) / m->ray->ray_dir_y;
	m->ray->line_height = (int)(m->height / m->ray->perp_wall_dist);
	m->ray->draw_start = -m->ray->line_height / 2 + m->height / 2;
	if (m->ray->draw_start < 0)
		m->ray->draw_start = 0;
	m->ray->draw_end = m->ray->line_height / 2 + m->height / 2;
	if (m->ray->draw_end >= m->height)
		m->ray->draw_end = m->height - 1;
}

void	draw_wall_slice(t_macro *m, int x)
{
	int	y;

	y = m->ray->draw_start;
	while (y < m->ray->draw_end)
	{
		mlx_put_pixel(m->images->scene_i, x, y, m->ray->wall_color);
		y++;
	}
}

void	paint_wall(t_macro *m)
{
	int	x;

	x = 0;
	while (x < m->width)
	{
		calculate_ray_direction(m, x);
		calculate_step_and_side_dist(m);
		perform_dda(m);
		calculate_wall_distance(m);
		if (m->ray->side == 1)
			m->ray->wall_color = get_rgba(255, 255, 255, 255);
		else
			m->ray->wall_color = get_rgba(220, 220, 220, 255);
		draw_wall_slice(m, x);
		x++;
	}
}

void	paint_background(t_macro *m)
{
	int	y;
	int	x;

	y = 0;
	while (y < (m->height) / 2)
	{
		x = 0;
		while (x < m->width)
			mlx_put_pixel(m->images->scene_i, x++, y, m->ray->ceiling);
		y++;
	}
	while (y < m->height)
	{
		x = 0;
		while (x < m->width)
			mlx_put_pixel(m->images->scene_i, x++, y, m->ray->floor);
		y++;
	}
}
