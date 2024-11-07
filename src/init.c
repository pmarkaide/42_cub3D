/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:45:44 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/07 10:56:26 by pmarkaid         ###   ########.fr       */
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
	macro->minimap = malloc(sizeof(t_minimap));
	if (!macro->minimap)
	{
		free(macro->m_mlx);
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
	if (mlx_image_to_window(mlx, image, 512, 512) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	load_images_into_struct(macro); // TODO: errors
	mlx_loop_hook(mlx, quit_hook, macro);
	mlx_loop(mlx);
	return (EXIT_SUCCESS);
}

mlx_image_t	*load_png_into_image(t_macro *macro, char *file)
{
	mlx_texture_t	*texture;
	mlx_image_t		*img;

	texture = mlx_load_png(file);
	if (!texture)
		free_and_exit(macro);
	img = mlx_texture_to_image(macro->m_mlx->mlx_cub, texture);
	if (!img)
		free_and_exit(macro);
	mlx_delete_texture(texture);
	return (img);
}

void	load_images_into_struct(t_macro *macro)
{
	// TODO: errors
	macro->minimap->background = load_png_into_image(macro, "textures/background.png");
	macro->minimap->wall = load_png_into_image(macro, "textures/wall.png");
	//macro->player = load_png_into_image(macro, "textures/player.png");
}
