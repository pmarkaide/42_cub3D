/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbejar-s <dbejar-s@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 23:26:44 by dbejar-s          #+#    #+#             */
/*   Updated: 2024/11/01 23:38:18 by dbejar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void calculate_wall_distance(t_macro *macro)
{
    if (macro->side == 0)
        macro->perp_wall_dist = (macro->map_x - macro->pos_pl_x / BLOCK + (1 - macro->step_x) / 2) / macro->ray_dir_x;
    else
        macro->perp_wall_dist = (macro->map_y - macro->pos_pl_y / BLOCK + (1 - macro->step_y) / 2) / macro->ray_dir_y;
    macro->line_height = (int)(macro->height / macro->perp_wall_dist);
    macro->draw_start = -macro->line_height / 2 + macro->height / 2;
    if (macro->draw_start < 0) macro->draw_start = 0;
    macro->draw_end = macro->line_height / 2 + macro->height / 2;
    if (macro->draw_end >= macro->height) macro->draw_end = macro->height - 1;
}

void draw_wall_slice(t_macro *macro, int x)
{
    int y = macro->draw_start;
    while (y < macro->draw_end)
    {
        mlx_put_pixel(macro->img, x, y, macro->wall_color);
        y++;
    }
}

void paint_wall(t_macro *macro)
{
    int x = 0;
    while (x < macro->width)
    {
        calculate_ray_direction(macro, x);
        calculate_step_and_side_dist(macro);
        perform_dda(macro);
        calculate_wall_distance(macro);
        if (macro->side == 1)
            macro->wall_color = ft_pixel(255, 255, 255, 255);
        else
            macro->wall_color = ft_pixel(220, 220, 220, 255);
        draw_wall_slice(macro, x);
        x++;
    }
}

void paint_background(t_macro *macro)
{
    int y = 0;
    while (y < (macro->height) / 2)
    {
        int x = 0;
        while (x < macro->width)
            mlx_put_pixel(macro->img, x++, y, macro->ceiling);
        y++;
    }
    while (y < macro->height)
    {
        int x = 0;
        while (x < macro->width)
            mlx_put_pixel(macro->img, x++, y, macro->floor);
        y++;
    }
}
