/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:49:54 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/19 14:57:15 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	stop_at_wall(t_macro *m, int x, int y)
{
	if (m->map->grid[(int)(y / BLOCK)][(int)(x / BLOCK)] != '1')
	{
		m->ray->pos_pl_x = x;
		m->ray->pos_pl_y = y;
	}
}

void	move_wsda(t_macro *m)
{
	int	*x;
	int	*y;

	x = &m->ray->pos_pl_x;
	y = &m->ray->pos_pl_y;
	if (m->keys->key_w)
	{
		*x += (int)(WALK_SPEED * cos(m->ray->play_angle));
		*y += (int)(WALK_SPEED * sin(m->ray->play_angle));
	}
	if (m->keys->key_a)
	{
		*x -= (int)(WALK_SPEED * cos(m->ray->play_angle + M_PI / 2));
		*y -= (int)(WALK_SPEED * sin(m->ray->play_angle + M_PI / 2));
	}
	if (m->keys->key_s)
	{
		*x -= (int)(WALK_SPEED * cos(m->ray->play_angle));
		*y -= (int)(WALK_SPEED * sin(m->ray->play_angle));
	}
	if (m->keys->key_d)
	{
		*x += (int)(WALK_SPEED * cos(m->ray->play_angle + M_PI / 2));
		*y += (int)(WALK_SPEED * sin(m->ray->play_angle + M_PI / 2));
	}
}

void	move_rotate(t_macro *m)
{
	if (m->keys->key_left)
	{
		m->ray->play_angle -= ROT_SPEED;
		m->ray->play_angle = fmod(m->ray->play_angle + 2 * M_PI, 2 * M_PI);
	}
	if (m->keys->key_right)
	{
		m->ray->play_angle += ROT_SPEED;
		m->ray->play_angle = fmod(m->ray->play_angle, 2 * M_PI);
	}
}
