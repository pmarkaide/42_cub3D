/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:20:28 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/19 15:18:45 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	initialize_vision_ray(t_macro *m, int x, double *ray_dir_x,
		double *ray_dir_y)
{
	double	camera_x;
	int		center_x;
	int		center_y;

	correct_player_pos_in_edge(m);
	center_x = m->ray->pos_pl_x;
	center_y = m->ray->pos_pl_y;
	camera_x = 2 * x / (double)m->width - 1;
	*ray_dir_x = cos(m->ray->play_angle) + camera_x * cos(m->ray->play_angle
			+ M_PI / 2);
	*ray_dir_y = sin(m->ray->play_angle) + camera_x * sin(m->ray->play_angle
			+ M_PI / 2);
	m->ray->map_x = (int)((center_x + BLOCK / 2) / BLOCK);
	m->ray->map_y = (int)((center_y + BLOCK / 2) / BLOCK);
	m->ray->delta_dist_x = fabs(1 / *ray_dir_x);
	m->ray->delta_dist_y = fabs(1 / *ray_dir_y);
	m->ray->hit = 0;
}

void	calculate_ray_steps(t_macro *m, double ray_dir_x, double ray_dir_y)
{
	calculate_ray_steps_x(m, ray_dir_x);
	calculate_ray_steps_y(m, ray_dir_y);
}

void	draw_ray(t_macro *m, float ray_length, double ray_dir_x,
		double ray_dir_y)
{
	float	dist;
	int		draw_x;
	int		draw_y;

	dist = 0.0f;
	correct_player_pos_in_edge(m);
	while (dist <= ray_length)
	{
		draw_x = m->ray->pos_pl_x + BLOCK / 2 + (int)(ray_dir_x * dist);
		draw_y = m->ray->pos_pl_y + BLOCK / 2 + (int)(ray_dir_y * dist);
		if (draw_x >= 0 && draw_x < (int)m->map->w_map * BLOCK && draw_y >= 0
			&& draw_y < (int)m->map->h_map * BLOCK)
		{
			if (m->map->grid[draw_y / BLOCK][draw_x / BLOCK] == '1')
				break ;
			mlx_put_pixel(m->images->mini_i, draw_x, draw_y, get_rgba(255, 255,
					255, 255));
		}
		dist += 0.5f;
	}
}

void	draw_vision_cone(t_macro *m)
{
	int		x;
	float	ray_length;
	double	ray_dir_x;
	double	ray_dir_y;

	x = 0;
	correct_player_pos_in_edge(m);
	while (x < m->width)
	{
		initialize_vision_ray(m, x, &ray_dir_x, &ray_dir_y);
		calculate_ray_steps(m, ray_dir_x, ray_dir_y);
		perform_dda(m);
		if (m->ray->side == 0)
			ray_length = ((m->ray->map_x - (m->ray->pos_pl_x + BLOCK / 2)
						/ BLOCK + (1 - m->ray->step_x) / 2) / ray_dir_x) * BLOCK
				* 2;
		else
			ray_length = ((m->ray->map_y - (m->ray->pos_pl_y + BLOCK) / BLOCK
						+ (1 - m->ray->step_y) / 2) / ray_dir_y) * BLOCK * 2;
		draw_ray(m, ray_length, ray_dir_x, ray_dir_y);
		x += 1;
	}
}

void	draw_minimap(t_macro *m)
{
	size_t	x;
	size_t	y;

	x = 0;
	while (x < m->map->h_map)
	{
		y = 0;
		while (y < m->map->w_map)
		{
			put_img2img(m->images->mini_i, m->images->background, y * BLOCK, x
				* BLOCK);
			if (m->map->grid[x][y] == '1')
				put_img2img(m->images->mini_i, m->images->wall, y * BLOCK, x
					* BLOCK);
			y += 1;
		}
		x += 1;
	}
	correct_player_pos_in_edge(m);
	printf("player position: %d, %d\n", m->ray->pos_pl_x, m->ray->pos_pl_y);
	put_img2img(m->images->mini_i, m->images->player, m->ray->pos_pl_x,
		m->ray->pos_pl_y);
	draw_vision_cone(m);
}
