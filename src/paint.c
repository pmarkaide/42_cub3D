/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbejar-s <dbejar-s@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 23:26:44 by dbejar-s          #+#    #+#             */
/*   Updated: 2024/11/22 00:58:19 by dbejar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void draw_texture_wall(t_macro *macro, int x)
{
    int y;
    int tex_x;
    int tex_y;
    mlx_texture_t *texture;
    double wall_x;
    double step;
    double tex_pos;
    uint8_t *pixel;
    uint32_t color;


    y = macro->ray->draw_start;
    if (macro->ray->side == 0)
        wall_x = macro->ray->pos_pl_y + macro->ray->perp_wall_dist * macro->ray->ray_dir_y;
    else
        wall_x = macro->ray->pos_pl_x + macro->ray->perp_wall_dist * macro->ray->ray_dir_x;
    wall_x -= floor(wall_x);

    if (macro->ray->side == 0 && macro->ray->ray_dir_x > 0)
        texture = macro->tex->we;
    if (macro->ray->side == 0 && macro->ray->ray_dir_x < 0)
        texture = macro->tex->ea;
    if (macro->ray->side == 1 && macro->ray->ray_dir_y > 0)
        texture = macro->tex->no;
    if (macro->ray->side == 1 && macro->ray->ray_dir_y < 0)
        texture = macro->tex->so;

    tex_x = (int)(wall_x * (double)texture->width);
    tex_x = texture->width - tex_x - 1;
    if (macro->ray->side == 0 && macro->ray->ray_dir_x > 0)
        tex_x = texture->width - tex_x - 1;
    if (macro->ray->side == 1 && macro->ray->ray_dir_y < 0)
        tex_x = texture->width - tex_x - 1;

    step = 1.0 * texture->height / macro->ray->line_height;
    tex_pos = (macro->ray->draw_start - macro->height / 2 + macro->ray->line_height / 2) * step;
    while (y < macro->ray->draw_end)
    {
        tex_y = (int)tex_pos;
        tex_pos += step;
        pixel = &((uint8_t *)texture->pixels)[(tex_y * texture->width + tex_x) * 4];
        color = get_rgba(pixel[0], pixel[1], pixel[2], pixel[3]);
        mlx_put_pixel(macro->images->scene_i, x, y, color);
        y++;
    }
}

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
		draw_texture_wall(m, x);
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
