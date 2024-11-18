/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbejar-s <dbejar-s@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 23:30:02 by dbejar-s          #+#    #+#             */
/*   Updated: 2024/11/06 07:47:41 by dbejar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	calculate_ray_direction(t_macro *macro, int x)
{
	macro->camera_x = 2 * x / (double)macro->width - 1;
	macro->ray_dir_x = cos(macro->play_angle) + macro->camera_x
		* cos(macro->play_angle + M_PI / 2);
	macro->ray_dir_y = sin(macro->play_angle) + macro->camera_x
		* sin(macro->play_angle + M_PI / 2);
	macro->map_x = (int)(macro->pos_pl_x / BLOCK);
	macro->map_y = (int)(macro->pos_pl_y / BLOCK);
	macro->delta_dist_x = fabs(1 / macro->ray_dir_x);
	macro->delta_dist_y = fabs(1 / macro->ray_dir_y);
	macro->hit = 0;
}

void	calculate_step_and_side_dist(t_macro *macro)
{
	if (macro->ray_dir_x < 0)
	{
		macro->step_x = -1;
		macro->side_dist_x = (macro->pos_pl_x / BLOCK - macro->map_x)
			* macro->delta_dist_x;
	}
	else
	{
		macro->step_x = 1;
		macro->side_dist_x = (macro->map_x + 1.0 - macro->pos_pl_x / BLOCK)
			* macro->delta_dist_x;
	}
	if (macro->ray_dir_y < 0)
	{
		macro->step_y = -1;
		macro->side_dist_y = (macro->pos_pl_y / BLOCK - macro->map_y)
			* macro->delta_dist_y;
	}
	else
	{
		macro->step_y = 1;
		macro->side_dist_y = (macro->map_y + 1.0 - macro->pos_pl_y / BLOCK)
			* macro->delta_dist_y;
	}
}

void	perform_dda(t_macro *macro)
{
	while (macro->hit == 0)
	{
		if (macro->side_dist_x < macro->side_dist_y)
		{
			macro->side_dist_x += macro->delta_dist_x;
			macro->map_x += macro->step_x;
			macro->side = 0;
		}
		else
		{
			macro->side_dist_y += macro->delta_dist_y;
			macro->map_y += macro->step_y;
			macro->side = 1;
		}
		if (macro->map->map[macro->map_y][macro->map_x] == '1')
			macro->hit = 1;
	}
}
