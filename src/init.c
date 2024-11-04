/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:45:44 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/04 14:44:07 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_macro	*init_macro(t_macro *macro)
{
	macro = malloc(sizeof(t_macro));
	if (!macro)
		return (NULL);
	bzero(macro, sizeof(t_macro));
	macro->map = malloc(sizeof(t_map));
	if (!macro->map)
	{
		free(macro);
		return (NULL);
	}
	bzero(macro->map, sizeof(t_map));
	macro->map->no = NULL;
	macro->map->so = NULL;
	macro->map->we = NULL;
	macro->map->ea = NULL;
	macro->map->map = NULL;
	return (macro);
}

// int32_t	game_init(t_map map)
// {
// 	mlx_t	*mlx;
// 	t_data	data;

// 	prepare_data_struct(&data, &map);
// 	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
// 	mlx = mlx_init(data.width, data.height, "Pac Man", true);
// 	if (!mlx)
// 		free_game_and_bad_exit(&data, "mlx initiation failed");
// 	load_images_into_struct(&data, mlx);
// 	render_map(&data);
// 	mlx_loop_hook(mlx, quit_hook, &data);
// 	mlx_loop_hook(mlx, exit_hook, &data);
// 	mlx_key_hook(mlx, (mlx_keyfunc)player_hook, &data);
// 	mlx_loop(mlx);
// 	return (0);
// }
