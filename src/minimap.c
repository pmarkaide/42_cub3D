/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:20:28 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/19 12:29:15 by pmarkaid         ###   ########.fr       */
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
	center_x = m->pos_pl_x;
	center_y = m->pos_pl_y;
	camera_x = 2 * x / (double)m->width - 1;
	*ray_dir_x = cos(m->play_angle) + camera_x * cos(m->play_angle
			+ M_PI / 2);
	*ray_dir_y = sin(m->play_angle) + camera_x * sin(m->play_angle
			+ M_PI / 2);
	m->map_x = (int)((center_x + BLOCK / 2) / BLOCK);
	m->map_y = (int)((center_y + BLOCK / 2) / BLOCK);
	m->delta_dist_x = fabs(1 / *ray_dir_x);
	m->delta_dist_y = fabs(1 / *ray_dir_y);
	m->hit = 0;
}

void	calculate_ray_steps(t_macro *m, double ray_dir_x, double ray_dir_y)
{
	float	center_x;
	float	center_y;

	center_x = m->pos_pl_x + BLOCK / 2;
	center_y = m->pos_pl_y + BLOCK / 2;
	if (ray_dir_x < 0)
	{
		m->step_x = -1;
		m->side_dist_x = (center_x / BLOCK - m->map_x) * m->delta_dist_x;
	}
	else
	{
		m->step_x = 1;
		m->side_dist_x = (m->map_x + 1.0 - center_x / BLOCK) * m->delta_dist_x;
	}
	if (ray_dir_y < 0)
	{
		m->step_y = -1;
		m->side_dist_y = (center_y / BLOCK - m->map_y) * m->delta_dist_y;
	}
	else
	{
		m->step_y = 1;
		m->side_dist_y = (m->map_y + 1.0 - center_y / BLOCK) * m->delta_dist_y;
	}
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
		draw_x = m->pos_pl_x + BLOCK / 2 + (int)(ray_dir_x * dist);
		draw_y = m->pos_pl_y + BLOCK / 2 + (int)(ray_dir_y * dist);
		if (draw_x >= 0 && draw_x < (int)m->map->w_map * 32 && draw_y >= 0
			&& draw_y < (int)m->map->h_map * 32)
		{
			if (m->map->grid[draw_y / BLOCK][draw_x / BLOCK] == '1')
				break ;
			mlx_put_pixel(m->mini_i, draw_x, draw_y, get_rgba(255, 255, 255,
					255));
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
		if (m->side == 0)
			ray_length = ((m->map_x - (m->pos_pl_x + BLOCK / 2) / BLOCK
						+ (1 - m->step_x) / 2) / ray_dir_x) * BLOCK * 2;
		else
			ray_length = ((m->map_y - (m->pos_pl_y + BLOCK) / BLOCK + (1
							- m->step_y) / 2) / ray_dir_y) * BLOCK * 2;
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
			put_img2img(m->mini_i, m->minimap->background, y * 32, x
				* 32);
			if (m->map->grid[x][y] == '1')
				put_img2img(m->mini_i, m->minimap->wall, y * 32, x
					* 32);
			y += 1;
		}
		x += 1;
	}
	correct_player_pos_in_edge(m);
	printf("player position: %d, %d\n", m->pos_pl_x, m->pos_pl_y);
	put_img2img(m->mini_i, m->minimap->player, m->pos_pl_x,
		m->pos_pl_y);
	draw_vision_cone(m);
}
