/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:46:15 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/19 15:18:28 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	correct_player_pos_in_edge(t_macro *m)
{
	if (m->ray->pos_pl_x < BLOCK)
		m->ray->pos_pl_x = BLOCK;
	else if (m->ray->pos_pl_x >= (int)m->map->w_map * BLOCK - BLOCK * 2)
		m->ray->pos_pl_x = m->map->w_map * BLOCK - BLOCK * 2;
	if (m->ray->pos_pl_y < BLOCK)
		m->ray->pos_pl_y = BLOCK;
	else if (m->ray->pos_pl_y >= (int)m->map->h_map * BLOCK - BLOCK * 2)
		m->ray->pos_pl_y = m->map->h_map * BLOCK - BLOCK * 2;
}

void	calculate_ray_steps_x(t_macro *m, double ray_dir_x)
{
	float	center_x;

	center_x = m->ray->pos_pl_x + BLOCK / 2;
	if (ray_dir_x < 0)
	{
		m->ray->step_x = -1;
		m->ray->side_dist_x = (center_x / BLOCK - m->ray->map_x)
			* m->ray->delta_dist_x;
	}
	else
	{
		m->ray->step_x = 1;
		m->ray->side_dist_x = (m->ray->map_x + 1.0 - center_x / BLOCK)
			* m->ray->delta_dist_x;
	}
}

void	calculate_ray_steps_y(t_macro *m, double ray_dir_y)
{
	float	center_y;

	center_y = m->ray->pos_pl_y + BLOCK / 2;
	if (ray_dir_y < 0)
	{
		m->ray->step_y = -1;
		m->ray->side_dist_y = (center_y / BLOCK - m->ray->map_y)
			* m->ray->delta_dist_y;
	}
	else
	{
		m->ray->step_y = 1;
		m->ray->side_dist_y = (m->ray->map_y + 1.0 - center_y / BLOCK)
			* m->ray->delta_dist_y;
	}
}
