/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 23:26:44 by dbejar-s          #+#    #+#             */
/*   Updated: 2024/11/19 12:29:28 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	calculate_wall_distance(t_macro *m)
{
	if (m->side == 0)
		m->perp_wall_dist = (m->map_x - m->pos_pl_x / BLOCK + (1
					- m->step_x) / 2) / m->ray_dir_x;
	else
		m->perp_wall_dist = (m->map_y - m->pos_pl_y / BLOCK + (1
					- m->step_y) / 2) / m->ray_dir_y;
	m->line_height = (int)(m->height / m->perp_wall_dist);
	m->draw_start = -m->line_height / 2 + m->height / 2;
	if (m->draw_start < 0)
		m->draw_start = 0;
	m->draw_end = m->line_height / 2 + m->height / 2;
	if (m->draw_end >= m->height)
		m->draw_end = m->height - 1;
}

void	draw_wall_slice(t_macro *m, int x)
{
	int	y;

	y = m->draw_start;
	while (y < m->draw_end)
	{
		mlx_put_pixel(m->scene_i, x, y, m->wall_color);
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
		if (m->side == 1)
			m->wall_color = get_rgba(255, 255, 255, 255);
		else
			m->wall_color = get_rgba(220, 220, 220, 255);
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
			mlx_put_pixel(m->scene_i, x++, y, m->ceiling);
		y++;
	}
	while (y < m->height)
	{
		x = 0;
		while (x < m->width)
			mlx_put_pixel(m->scene_i, x++, y, m->floor);
		y++;
	}
}
