/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 23:30:02 by dbejar-s          #+#    #+#             */
/*   Updated: 2024/11/19 12:23:29 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	calculate_ray_direction(t_macro *m, int x)
{
	m->camera_x = 2 * x / (double)m->width - 1;
	m->ray_dir_x = cos(m->play_angle) + m->camera_x
		* cos(m->play_angle + M_PI / 2);
	m->ray_dir_y = sin(m->play_angle) + m->camera_x
		* sin(m->play_angle + M_PI / 2);
	m->map_x = (int)(m->pos_pl_x / BLOCK);
	m->map_y = (int)(m->pos_pl_y / BLOCK);
	m->delta_dist_x = fabs(1 / m->ray_dir_x);
	m->delta_dist_y = fabs(1 / m->ray_dir_y);
	m->hit = 0;
}

void	calculate_step_and_side_dist(t_macro *m)
{
	if (m->ray_dir_x < 0)
	{
		m->step_x = -1;
		m->side_dist_x = (m->pos_pl_x / BLOCK - m->map_x)
			* m->delta_dist_x;
	}
	else
	{
		m->step_x = 1;
		m->side_dist_x = (m->map_x + 1.0 - m->pos_pl_x / BLOCK)
			* m->delta_dist_x;
	}
	if (m->ray_dir_y < 0)
	{
		m->step_y = -1;
		m->side_dist_y = (m->pos_pl_y / BLOCK - m->map_y)
			* m->delta_dist_y;
	}
	else
	{
		m->step_y = 1;
		m->side_dist_y = (m->map_y + 1.0 - m->pos_pl_y / BLOCK)
			* m->delta_dist_y;
	}
}

void	perform_dda(t_macro *m)
{
	while (m->hit == 0)
	{
		if (m->side_dist_x < m->side_dist_y)
		{
			m->side_dist_x += m->delta_dist_x;
			m->map_x += m->step_x;
			m->side = 0;
		}
		else
		{
			m->side_dist_y += m->delta_dist_y;
			m->map_y += m->step_y;
			m->side = 1;
		}
		if (m->map->grid[m->map_y][m->map_x] == '1')
			m->hit = 1;
	}
}
