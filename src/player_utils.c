/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:49:54 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/12/27 21:02:04 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * Moves the player in the specified direction if the new position is valid.
 * 
 * @param m Pointer to the macro structure containing player and map information.
 * @param x The x-coordinate offset for the movement.
 * @param y The y-coordinate offset for the movement.
 */
void	move_wsda(t_macro *m, double x, double y)
{
	int	map_pos_x;
	int	map_pos_y;
	int	new_pos_x;
	int	new_pos_y;

	new_pos_x = roundf(m->ray->pos_pl_x + x);
	new_pos_y = roundf(m->ray->pos_pl_y + y);
	map_pos_x = new_pos_x / BLOCK;
	map_pos_y = new_pos_y / BLOCK;
	if ((map_pos_x >= BUFF_AREA) && (map_pos_x < (m->map->w_buff - BUFF_AREA))
		&& map_pos_y >= BUFF_AREA && (map_pos_y < (m->map->h_buff - BUFF_AREA)))
	{
		m->ray->pos_pl_x = new_pos_x;
		m->ray->pos_pl_y = new_pos_y;
	}
}

/**
 * Calculates the movement direction based on the pressed keys (W, A, S, D).
 * 
 * @param m Pointer to the macro structure containing player and map information.
 * @param x The x-coordinate offset for the movement.
 * @param y The y-coordinate offset for the movement.
 */
void	get_wsda(t_macro *m, double x, double y)
{
	double	angle;

	angle = m->ray->play_angle;
	if (m->keys->key_w)
	{
		x = WALK_SPEED * cos(angle);
		y = WALK_SPEED * sin(angle);
	}
	else if (m->keys->key_a)
	{
		x = WALK_SPEED * sin(angle);
		y = WALK_SPEED * cos(angle + M_PI);
	}
	else if (m->keys->key_s)
	{
		x = WALK_SPEED * cos(angle + M_PI);
		y = WALK_SPEED * sin(angle + M_PI);
	}
	else if (m->keys->key_d)
	{
		x = WALK_SPEED * sin(angle + M_PI);
		y = WALK_SPEED * cos(angle);
	}
	move_wsda(m, x, y);
}

/**
 * Handles the player's movement and rotation based on the pressed keys.
 * 
 * @param m Pointer to the macro structure containing player and map information.
 */
void	move(t_macro *m)
{
	double	x;
	double	y;

	x = 0;
	y = 0;
	get_wsda(m, x, y);
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
