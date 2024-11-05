/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:45:44 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/05 15:28:21 by pmarkaid         ###   ########.fr       */
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

int32_t	init_game(t_macro *macro)
{
	mlx_t	*mlx;

	mlx = mlx_init(WIDTH, HEIGHT, "cubeD", false);
	if (!mlx)
		free_and_exit(macro);
	render_minimap(macro);
	mlx_loop_hook(mlx, quit_hook, macro);
	//mlx_key_hook(mlx, (mlx_keyfunc)player_hook, &data);
	mlx_loop(mlx);
	return (0);
}
