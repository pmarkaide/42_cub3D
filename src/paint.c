/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 23:26:44 by dbejar-s          #+#    #+#             */
/*   Updated: 2024/11/19 13:22:03 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	calculate_wall_distance(t_macro *m)
{
	if (m->raycast->side == 0)
		m->raycast->perp_wall_dist = (m->raycast->map_x - m->raycast->pos_pl_x / BLOCK + (1
					- m->raycast->step_x) / 2) / m->raycast->ray_dir_x;
	else
		m->raycast->perp_wall_dist = (m->raycast->map_y - m->raycast->pos_pl_y / BLOCK + (1
					- m->raycast->step_y) / 2) / m->raycast->ray_dir_y;
	m->raycast->line_height = (int)(m->height / m->raycast->perp_wall_dist);
	m->raycast->draw_start = -m->raycast->line_height / 2 + m->height / 2;
	if (m->raycast->draw_start < 0)
		m->raycast->draw_start = 0;
	m->raycast->draw_end = m->raycast->line_height / 2 + m->height / 2;
	if (m->raycast->draw_end >= m->height)
		m->raycast->draw_end = m->height - 1;
}

void	draw_wall_slice(t_macro *m, int x)
{
	int	y;

	y = m->raycast->draw_start;
	while (y < m->raycast->draw_end)
	{
		mlx_put_pixel(m->images->scene_i, x, y, m->raycast->wall_color);
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
		if (m->raycast->side == 1)
			m->raycast->wall_color = get_rgba(255, 255, 255, 255);
		else
			m->raycast->wall_color = get_rgba(220, 220, 220, 255);
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
			mlx_put_pixel(m->images->scene_i, x++, y, m->raycast->ceiling);
		y++;
	}
	while (y < m->height)
	{
		x = 0;
		while (x < m->width)
			mlx_put_pixel(m->images->scene_i, x++, y, m->raycast->floor);
		y++;
	}
}
