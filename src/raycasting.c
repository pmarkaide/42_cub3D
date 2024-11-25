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

void	my_mlx_pixel_put(t_macro *m, int x, int y, int color)
{
	if (x < 0)
		return ;
	else if (x >= m->width)
		return ;
	if (y < 0)
		return ;
	else if (y >= m->height)
		return ;
	mlx_put_pixel(m->images->scene_i, x, y, color);
}

void	draw_wall(t_macro *m, int t_pix, int b_pix, double wall_h)
{
	double			x_o;
	double			y_o;
	mlx_texture_t	*texture;
	uint32_t		*arr;
	double			factor;

	texture = get_texture(m, m->ray->hit);
	arr = (uint32_t *)texture->pixels;
	factor = (double)texture->height / wall_h;
	x_o = get_x_o(texture, m);
	y_o = (t_pix - (m->height / 2) + (wall_h / 2)) * factor;
	if (y_o < 0)
		y_o = 0;
	while (t_pix < b_pix)
	{
		my_mlx_pixel_put(m, m->ray->index, t_pix,
			reverse_bytes(arr[(int)y_o * texture->width + (int)x_o]));
		y_o += factor;
		t_pix++;
	}
}

void	draw_floor_ceiling(t_macro *m, int ray, int t_pix, int b_pix)
{
	int		i;
	int		c;

	i = b_pix;
	c = m->ray->floor;
	while (i < m->height)
		my_mlx_pixel_put(m, ray, i++, c);
	c = m->ray->ceiling;
	i = 0;
	while (i < t_pix)
		my_mlx_pixel_put(m, ray, i++, c);
}

void	do_wall(t_macro *m, int vertical)
{
	double	wall_h;
	double	b_pix;
	double	t_pix;

	m->ray->distance *= cos(nor_angle(m->ray->ray_angle - m->ray->play_angle));
	wall_h = (BLOCK / m->ray->distance) * ((m->width / 2) / \
	tan(m->ray->play_view / 2));
	b_pix = (m->height / 2) + (wall_h / 2);
	t_pix = (m->height / 2) - (wall_h / 2);
	if (b_pix > m->height)
		b_pix = m->height;
	if (t_pix < 0)
		t_pix = 0;
	m->ray->index = vertical;
	draw_floor_ceiling(m, vertical, b_pix, t_pix);
	draw_wall(m, t_pix, b_pix, wall_h);
}

void	raycast(t_macro *m)
{
	double	x_cross;
	double	y_cross;
	int		vertical;

	vertical = 0;
	m->ray->ray_angle = m->ray->play_angle - (m->ray->play_view / 2);
	while (vertical < m->width)
	{
		m->ray->hit = 0;
		x_cross = x_dda(m, fmod(m->ray->ray_angle, 2 * M_PI));
		y_cross = y_dda(m, fmod(m->ray->ray_angle, 2 * M_PI));
		if (x_cross < y_cross)
		{
			m->ray->distance = x_cross;
			m->ray->hit = 1;
		}
		else
			m->ray->distance = y_cross;
		do_wall(m, vertical);
		vertical++;
		m->ray->ray_angle += m->ray->play_view / m->width;
	}
}
