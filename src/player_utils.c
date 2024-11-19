/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:49:54 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/19 12:23:29 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	stop_at_wall(t_macro *m, int x, int y)
{
	if (m->map->grid[(int)(y / BLOCK)][(int)(x / BLOCK)] != '1')
	{
		m->pos_pl_x = x;
		m->pos_pl_y = y;
	}
}

void	move_wsda(t_macro *m)
{
	int	*x;
	int	*y;

	x = &m->pos_pl_x;
	y = &m->pos_pl_y;
	if (m->key_w)
	{
		*x += (int)(WALK_SPEED * cos(m->play_angle));
		*y += (int)(WALK_SPEED * sin(m->play_angle));
	}
	if (m->key_a)
	{
		*x -= (int)(WALK_SPEED * cos(m->play_angle + M_PI / 2));
		*y -= (int)(WALK_SPEED * sin(m->play_angle + M_PI / 2));
	}
	if (m->key_s)
	{
		*x -= (int)(WALK_SPEED * cos(m->play_angle));
		*y -= (int)(WALK_SPEED * sin(m->play_angle));
	}
	if (m->key_d)
	{
		*x += (int)(WALK_SPEED * cos(m->play_angle + M_PI / 2));
		*y += (int)(WALK_SPEED * sin(m->play_angle + M_PI / 2));
	}
}

void	move_rotate(t_macro *m)
{
	if (m->key_left)
	{
		m->play_angle -= ROT_SPEED;
		m->play_angle = fmod(m->play_angle + 2 * M_PI, 2 * M_PI);
	}
	if (m->key_right)
	{
		m->play_angle += ROT_SPEED;
		m->play_angle = fmod(m->play_angle, 2 * M_PI);
	}
}
