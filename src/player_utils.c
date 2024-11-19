/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:49:54 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/19 10:51:21 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	stop_at_wall(t_macro *macro, int x, int y)
{
	if (macro->map->grid[(int)(y / BLOCK)][(int)(x / BLOCK)] != '1')
	{
		macro->pos_pl_x = x;
		macro->pos_pl_y = y;
	}
}

void	move_wsda(t_macro *macro)
{
	int	*x;
	int	*y;

	x = &macro->pos_pl_x;
	y = &macro->pos_pl_y;
	if (macro->key_w)
	{
		*x += (int)(WALK_SPEED * cos(macro->play_angle));
		*y += (int)(WALK_SPEED * sin(macro->play_angle));
	}
	if (macro->key_a)
	{
		*x -= (int)(WALK_SPEED * cos(macro->play_angle + M_PI / 2));
		*y -= (int)(WALK_SPEED * sin(macro->play_angle + M_PI / 2));
	}
	if (macro->key_s)
	{
		*x -= (int)(WALK_SPEED * cos(macro->play_angle));
		*y -= (int)(WALK_SPEED * sin(macro->play_angle));
	}
	if (macro->key_d)
	{
		*x += (int)(WALK_SPEED * cos(macro->play_angle + M_PI / 2));
		*y += (int)(WALK_SPEED * sin(macro->play_angle + M_PI / 2));
	}
}

void	move_rotate(t_macro *macro)
{
	if (macro->key_left)
	{
		macro->play_angle -= ROT_SPEED;
		macro->play_angle = fmod(macro->play_angle + 2 * M_PI, 2 * M_PI);
	}
	if (macro->key_right)
	{
		macro->play_angle += ROT_SPEED;
		macro->play_angle = fmod(macro->play_angle, 2 * M_PI);
	}
}
