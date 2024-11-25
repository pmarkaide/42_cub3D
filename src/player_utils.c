/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbejar-s <dbejar-s@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:49:54 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/25 22:59:47 by dbejar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
	if (m->map->grid[map_pos_y][map_pos_x] != '1') //más condiciones en mapa ampliado con cerossss?????
	{
		m->ray->pos_pl_x = new_pos_x;
		m->ray->pos_pl_y = new_pos_y;
	}
}

void get_wsda(t_macro *m, double x, double y)
{
    double angle;
	
	angle = m->ray->play_angle;
    if (m->keys->key_w)
    {
        x = WALK_SPEED * cos(angle);
        y = WALK_SPEED * sin(angle);
    }
    else if (m->keys->key_a)
    {
        x = WALK_SPEED * sin(angle);
        y = WALK_SPEED * -cos(angle);
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

void	move(t_macro *m)
{
	get_wsda(m, 0, 0);
	move_rotate(m);
}
