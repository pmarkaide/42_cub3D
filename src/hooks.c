/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 10:39:43 by dbejar-s          #+#    #+#             */
/*   Updated: 2024/11/07 11:04:28 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void quit_hook(void *param)
{
    t_macro *macro;

    if (!param)
        return;
    macro = (t_macro *)param;
    if (!macro->mlx_cub || !macro->mlx_cub)
        return;
    if (mlx_is_key_down(macro->mlx_cub, MLX_KEY_ESCAPE))
        free_and_exit(macro);
}

void ft_hook(mlx_key_data_t keydata, void *param)
{
    t_macro *macro;
    double rot_speed;
	
	macro = (t_macro *)param;
	rot_speed = 0.05;
    if (keydata.key == MLX_KEY_ESCAPE && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
        mlx_close_window(macro->mlx_cub);
    if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
    {
        if (keydata.key == MLX_KEY_LEFT)
        {
            macro->play_angle -= rot_speed;
            if (macro->play_angle < 0)
                macro->play_angle += 2 * M_PI;
        }
        if (keydata.key == MLX_KEY_RIGHT)
        {
            macro->play_angle += rot_speed;
            if (macro->play_angle > 2 * M_PI)
                macro->play_angle -= 2 * M_PI;
        }
        load_game(macro);
	}
}
