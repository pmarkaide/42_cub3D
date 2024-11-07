/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:45:44 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/07 11:31:07 by pmarkaid         ###   ########.fr       */
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
	macro->minimap = malloc(sizeof(t_minimap));
	if (!macro->minimap)
	{
		free(macro->mlx_cub);
		free(macro->map);
		free(macro);
		return (NULL);
	}
	return (macro);
}
mlx_image_t	*load_png_into_image(t_macro *macro, char *file)
{
	mlx_texture_t	*texture;
	mlx_image_t		*img;

	texture = mlx_load_png(file);
	if (!texture)
		free_and_exit(macro);
	img = mlx_texture_to_image(macro->mlx_cub, texture);
	if (!img)
		free_and_exit(macro);
	mlx_delete_texture(texture);
	return (img);
}

void	load_images_into_struct(t_macro *macro)
{
	// TODO: errors
	macro->minimap->background = load_png_into_image(macro, "textures/background.png");
	if(!macro->minimap->background)
		free_and_exit(macro);
	macro->minimap->wall = load_png_into_image(macro, "textures/wall.png");
	if(!macro->minimap->wall)
		free_and_exit(macro);
	//macro->player = load_png_into_image(macro, "textures/player.png");
}
