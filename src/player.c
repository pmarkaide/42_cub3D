/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 07:01:36 by dbejar-s          #+#    #+#             */
/*   Updated: 2024/11/19 14:57:15 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	move(t_macro *m)
{
	move_wsda(m);
	move_rotate(m);
	stop_at_wall(m, m->ray->pos_pl_x, m->ray->pos_pl_y);
}

void	load_game(void *param)
{
	t_macro	*m;

	m = (t_macro *)param;
	move(m);
	paint_background(m);
	paint_wall(m);
	draw_minimap(m);
}

void	load_player(t_macro *m)
{
	m->ray->pos_pl_x = m->map->start_x * BLOCK + BLOCK / 2;
	m->ray->pos_pl_y = m->map->start_y * BLOCK + BLOCK / 2;
	m->ray->play_view = M_PI * ANGLE_VIEW / 180;
	if (m->map->orientation == 'N')
		m->ray->play_angle = 3 * M_PI / 2;
	else if (m->map->orientation == 'E')
		m->ray->play_angle = 0;
	else if (m->map->orientation == 'S')
		m->ray->play_angle = M_PI / 2;
	else if (m->map->orientation == 'W')
		m->ray->play_angle = M_PI;
}

void	player_in_map(t_macro *m)
{
	int	y;
	int	x;

	y = 0;
	while (m->map->grid[y] != NULL)
	{
		x = 0;
		while (m->map->grid[y][x])
		{
			if (m->map->grid[y][x] == 'N' || m->map->grid[y][x] == 'S'
				|| m->map->grid[y][x] == 'E' || m->map->grid[y][x] == 'W')
			{
				m->map->start_x = x;
				m->map->start_y = y;
				m->map->orientation = m->map->grid[y][x];
				m->map->grid[y][x] = '0';
				break ;
			}
			x++;
		}
		y++;
	}
}

void	load_map(t_macro *m)
{
	m->ray->floor = get_rgba(m->map->f[0], m->map->f[1], m->map->f[2], 255);
	m->ray->ceiling = get_rgba(m->map->c[0], m->map->c[1], m->map->c[2], 255);
	player_in_map(m);
}
