/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:45:44 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/05 16:58:12 by pmarkaid         ###   ########.fr       */
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
	macro->m_mlx = (t_mlx *)malloc(sizeof(t_mlx));
	if (!macro->m_mlx)
	{
		free(macro->map);
		free(macro);
		return (NULL);
	}
	return (macro);
}
int32_t init_game(t_macro *macro)
{
	mlx_t* mlx;
	mlx_image_t* image;

	// Gotta error check this stuff
	if (!(macro->m_mlx->mlx_cub = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	mlx = macro->m_mlx->mlx_cub;
	if (!(macro->m_mlx->img = mlx_new_image(mlx, 512, 512)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	image = macro->m_mlx->img;
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	mlx_loop_hook(mlx, quit_hook, macro);
	mlx_loop(mlx);
	return (EXIT_SUCCESS);
}
