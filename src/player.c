/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/11/15 14:09:11 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/cub3D.h"


void move(t_macro *macro)
{
    if (macro->key_w)
    {
        macro->pos_pl_x += WALK_SPEED * cos(macro->play_angle);
        macro->pos_pl_y += WALK_SPEED * sin(macro->play_angle);
    }
    if (macro->key_a)
    {
        macro->pos_pl_x -= WALK_SPEED * cos(macro->play_angle + M_PI / 2);
        macro->pos_pl_y -= WALK_SPEED * sin(macro->play_angle + M_PI / 2);
    }
    if (macro->key_s)
    {
        macro->pos_pl_x -= WALK_SPEED * cos(macro->play_angle);
        macro->pos_pl_y -= WALK_SPEED * sin(macro->play_angle);
    }
    if (macro->key_d)
    {
        macro->pos_pl_x += WALK_SPEED * cos(macro->play_angle + M_PI / 2);
        macro->pos_pl_y += WALK_SPEED * sin(macro->play_angle + M_PI / 2);
    }
    if (macro->key_left)
    {
        macro->play_angle -= ROT_SPEED;
        if (macro->play_angle < 0)
            macro->play_angle += 2 * M_PI;
    }
    if (macro->key_right)
    {
        macro->play_angle += ROT_SPEED;
        if (macro->play_angle > 2 * M_PI)
            macro->play_angle -= 2 * M_PI;  
    }

}

void load_game(void *param)
{
    t_macro *macro;
    
    macro = (t_macro*)param;
    move(macro);
    paint_background(macro);
    paint_wall(macro);
    //draw_minimap(macro);
   
}

void load_player(t_macro *macro)
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

void    player_in_map(t_macro *macro)
{
    int y;
    int x;

    y = 0;
    while (macro->map->map[y] != NULL)
    {
        x = 0;
        while (macro->map->map[y][x])
        {
            if (macro->map->map[y][x] == 'N' || macro->map->map[y][x] == 'S' || macro->map->map[y][x] == 'E' || macro->map->map[y][x] == 'W')
            {
                macro->start_x = x;
                macro->start_y = y;
                macro->orientation = macro->map->map[y][x];
                macro->map->map[y][x] = '0';
                break ;
            }
            x++;
        }
        y++;
    }
}

void    load_map(t_macro *macro)
{
    //int rows, cols;
    //macro->map = parse_map(file, &rows, &cols);
    macro->floor = ft_pixel(macro->map->f[0], macro->map->f[1], macro->map->f[2], 255);
    macro->ceiling = ft_pixel(macro->map->c[0], macro->map->c[1], macro->map->c[2], 255);
    player_in_map(macro);
    // macro->start_x = 10;
    // macro->start_y = 7;
    // macro->orientation = 'E';
}
