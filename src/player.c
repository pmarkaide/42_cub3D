/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 07:01:36 by dbejar-s          #+#    #+#             */
/*   Updated: 2024/11/18 16:01:23 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"
#include <stdio.h>

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

void	move(t_macro *macro)
{
	move_wsda(macro);
	move_rotate(macro);
	stop_at_wall(macro, macro->pos_pl_x, macro->pos_pl_y);
}

void	load_game(void *param)
{
	t_macro	*macro;

	macro = (t_macro *)param;
	move(macro);
	paint_background(macro);
	paint_wall(macro);
	draw_minimap(macro);
}

void	load_player(t_macro *macro)
{
	macro->pos_pl_x = macro->start_x * BLOCK + BLOCK / 2;
	macro->pos_pl_y = macro->start_y * BLOCK + BLOCK / 2;
	macro->play_view = M_PI * ANGLE_VIEW / 180;
	if (macro->orientation == 'N')
		macro->play_angle = 3 * M_PI / 2;
	else if (macro->orientation == 'E')
		macro->play_angle = 0;
	else if (macro->orientation == 'S')
		macro->play_angle = M_PI / 2;
	else if (macro->orientation == 'W')
		macro->play_angle = M_PI;
}

void	player_in_map(t_macro *macro)
{
	int	y;
	int	x;

	y = 0;
	while (macro->map->grid[y] != NULL)
	{
		x = 0;
		while (macro->map->grid[y][x])
		{
			if (macro->map->grid[y][x] == 'N' || macro->map->grid[y][x] == 'S'
				|| macro->map->grid[y][x] == 'E'
				|| macro->map->grid[y][x] == 'W')
			{
				macro->start_x = x;
				macro->start_y = y;
				macro->orientation = macro->map->grid[y][x];
				macro->map->grid[y][x] = '0';
				break ;
			}
			x++;
		}
		y++;
	}
}

void	load_map(t_macro *macro)
{
	macro->floor = get_rgba(macro->map->f[0], macro->map->f[1],
			macro->map->f[2], 255);
	macro->ceiling = get_rgba(macro->map->c[0], macro->map->c[1],
			macro->map->c[2], 255);
	player_in_map(macro);
}
