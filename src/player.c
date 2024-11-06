/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbejar-s <dbejar-s@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 07:01:36 by dbejar-s          #+#    #+#             */
/*   Updated: 2024/11/06 07:43:46 by dbejar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void load_game(t_macro *macro)
{
    mlx_delete_image(macro->mlx_cub, macro->img);
    macro->img = mlx_new_image(macro->mlx_cub, macro->width, macro->height);
    paint_background(macro);
    paint_wall(macro);
    mlx_image_to_window(macro->mlx_cub, macro->img, 0, 0);
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
