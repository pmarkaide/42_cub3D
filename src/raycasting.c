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

void	calculate_ray_direction(t_macro *m, int x)
{
	m->ray->camera_x = 2 * x / (double)m->width - 1;
	m->ray->ray_dir_x = cos(m->ray->play_angle) + m->ray->camera_x
		* cos(m->ray->play_angle + M_PI / 2);
	m->ray->ray_dir_y = sin(m->ray->play_angle) + m->ray->camera_x
		* sin(m->ray->play_angle + M_PI / 2);
	m->ray->map_x = (int)(m->ray->pos_pl_x / BLOCK);
	m->ray->map_y = (int)(m->ray->pos_pl_y / BLOCK);
	m->ray->delta_dist_x = fabs(1 / m->ray->ray_dir_x);
	m->ray->delta_dist_y = fabs(1 / m->ray->ray_dir_y);
	m->ray->hit = 0;
}

void	calculate_step_and_side_dist(t_macro *m)
{
	if (m->ray->ray_dir_x < 0)
	{
		m->ray->step_x = -1;
		m->ray->side_dist_x = (m->ray->pos_pl_x / BLOCK - m->ray->map_x)
			* m->ray->delta_dist_x;
	}
	else
	{
		m->ray->step_x = 1;
		m->ray->side_dist_x = (m->ray->map_x + 1.0 - m->ray->pos_pl_x / BLOCK)
			* m->ray->delta_dist_x;
	}
	if (m->ray->ray_dir_y < 0)
	{
		m->ray->step_y = -1;
		m->ray->side_dist_y = (m->ray->pos_pl_y / BLOCK - m->ray->map_y)
			* m->ray->delta_dist_y;
	}
	else
	{
		m->ray->step_y = 1;
		m->ray->side_dist_y = (m->ray->map_y + 1.0 - m->ray->pos_pl_y / BLOCK)
			* m->ray->delta_dist_y;
	}
}

void	perform_dda(t_macro *m)
{
	while (m->ray->hit == 0)
	{
		if (m->ray->side_dist_x < m->ray->side_dist_y)
		{
			m->ray->side_dist_x += m->ray->delta_dist_x;
			m->ray->map_x += m->ray->step_x;
			m->ray->side = 0;
		}
		else
		{
			m->ray->side_dist_y += m->ray->delta_dist_y;
			m->ray->map_y += m->ray->step_y;
			m->ray->side = 1;
		}
		if (m->map->grid[m->ray->map_y][m->ray->map_x] == '1')
			m->ray->hit = 1;
	}
}
