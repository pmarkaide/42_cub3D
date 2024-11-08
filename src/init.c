/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbejar-s <dbejar-s@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:45:44 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/08 13:00:19 by dbejar-s         ###   ########.fr       */
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
	macro->key_w = 0;
	macro->key_a = 0;
	macro->key_s = 0;
	macro->key_d = 0;
	macro->key_left = 0;
	macro->key_right = 0;
	return (macro);
}

void adjust_image_transparency(mlx_texture_t* texture, float alpha_factor) {
    if (!texture || alpha_factor < 0.0f || alpha_factor > 1.0f) return;

    uint32_t y = 0;
    while (y < texture->height) {
        uint32_t x = 0;
        while (x < texture->width) {
            uint8_t* pixel = &texture->pixels[(y * texture->width + x) * 4];
            pixel[3] = (uint8_t)(pixel[3] * alpha_factor);
            x++;
        }
        y++;
    }
}

mlx_image_t	*load_png_into_image(t_macro *macro, char *file)
{
	mlx_texture_t	*texture;
	mlx_image_t		*img;

	texture = mlx_load_png(file);
	if (!texture)
		free_and_exit(macro);
	adjust_image_transparency(texture, 0.5f);
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
	macro->minimap->player = load_png_into_image(macro, "textures/player.png");
}
