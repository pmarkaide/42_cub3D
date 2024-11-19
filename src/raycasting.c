/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 23:30:02 by dbejar-s          #+#    #+#             */
/*   Updated: 2024/11/19 13:14:50 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	calculate_ray_direction(t_macro *m, int x)
{
	m->raycast->camera_x = 2 * x / (double)m->width - 1;
	m->raycast->ray_dir_x = cos(m->raycast->play_angle) + m->raycast->camera_x
		* cos(m->raycast->play_angle + M_PI / 2);
	m->raycast->ray_dir_y = sin(m->raycast->play_angle) + m->raycast->camera_x
		* sin(m->raycast->play_angle + M_PI / 2);
	m->raycast->map_x = (int)(m->raycast->pos_pl_x / BLOCK);
	m->raycast->map_y = (int)(m->raycast->pos_pl_y / BLOCK);
	m->raycast->delta_dist_x = fabs(1 / m->raycast->ray_dir_x);
	m->raycast->delta_dist_y = fabs(1 / m->raycast->ray_dir_y);
	m->raycast->hit = 0;
}

void	calculate_step_and_side_dist(t_macro *m)
{
	if (m->raycast->ray_dir_x < 0)
	{
		m->raycast->step_x = -1;
		m->raycast->side_dist_x = (m->raycast->pos_pl_x / BLOCK - m->raycast->map_x)
			* m->raycast->delta_dist_x;
	}
	else
	{
		m->raycast->step_x = 1;
		m->raycast->side_dist_x = (m->raycast->map_x + 1.0 - m->raycast->pos_pl_x / BLOCK)
			* m->raycast->delta_dist_x;
	}
	if (m->raycast->ray_dir_y < 0)
	{
		m->raycast->step_y = -1;
		m->raycast->side_dist_y = (m->raycast->pos_pl_y / BLOCK - m->raycast->map_y)
			* m->raycast->delta_dist_y;
	}
	else
	{
		m->raycast->step_y = 1;
		m->raycast->side_dist_y = (m->raycast->map_y + 1.0 - m->raycast->pos_pl_y / BLOCK)
			* m->raycast->delta_dist_y;
	}
}

void	perform_dda(t_macro *m)
{
	while (m->raycast->hit == 0)
	{
		if (m->raycast->side_dist_x < m->raycast->side_dist_y)
		{
			m->raycast->side_dist_x += m->raycast->delta_dist_x;
			m->raycast->map_x += m->raycast->step_x;
			m->raycast->side = 0;
		}
		else
		{
			m->raycast->side_dist_y += m->raycast->delta_dist_y;
			m->raycast->map_y += m->raycast->step_y;
			m->raycast->side = 1;
		}
		if (m->map->grid[m->raycast->map_y][m->raycast->map_x] == '1')
			m->raycast->hit = 1;
	}
}
