/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:12:51 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/19 12:26:06 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_macro	*init_macro(t_macro *m)
{
	m = malloc(sizeof(t_macro));
	if (!m)
		return (NULL);
	bzero(m, sizeof(t_macro));
	m->map = malloc(sizeof(t_map));
	if (!m->map)
	{
		free(m);
		return (NULL);
	}
	bzero(m->map, sizeof(t_map));
	m->map->no = NULL;
	m->map->so = NULL;
	m->map->we = NULL;
	m->map->ea = NULL;
	m->map->grid = NULL;
	m->minimap = malloc(sizeof(t_minimap));
	if (!m->minimap)
	{
		free(m->map);
		free(m);
		return (NULL);
	}
	m->mini_i = NULL;
	return (m);
}

void	adjust_image_transparency(mlx_texture_t *texture, float alpha_factor)
{
	uint32_t	y;
	uint32_t	x;
	uint8_t		*pixel;

	if (!texture || alpha_factor < 0.0f || alpha_factor > 1.0f)
		return ;
	y = 0;
	while (y < texture->height)
	{
		x = 0;
		while (x < texture->width)
		{
			pixel = &texture->pixels[(y * texture->width + x) * 4];
			pixel[3] = (uint8_t)(pixel[3] * alpha_factor);
			x++;
		}
		y++;
	}
}

mlx_image_t	*load_png_into_image(t_macro *m, char *file)
{
	mlx_texture_t	*texture;
	mlx_image_t		*img;

	texture = mlx_load_png(file);
	if (!texture)
		free_and_exit(m);
	adjust_image_transparency(texture, 0.5f);
	img = mlx_texture_to_image(m->mlx_cub, texture);
	if (!img)
		free_and_exit(m);
	mlx_delete_texture(texture);
	return (img);
}

void	unload_images_from_struct(t_macro *m)
{
	if (m->minimap->background)
	{
		mlx_delete_image(m->mlx_cub, m->minimap->background);
		m->minimap->background = NULL;
	}
	if (m->minimap->wall)
	{
		mlx_delete_image(m->mlx_cub, m->minimap->wall);
		m->minimap->wall = NULL;
	}
	if (m->minimap->player)
	{
		mlx_delete_image(m->mlx_cub, m->minimap->player);
		m->minimap->player = NULL;
	}
}

void	load_images_into_struct(t_macro *m)
{
	m->minimap->background = load_png_into_image(m,"textures/background.png");
	if (!m->minimap->background)
		free_and_exit(m);
	m->minimap->wall = load_png_into_image(m, "textures/wall.png");
	if (!m->minimap->wall)
		free_and_exit(m);
	m->minimap->player = load_png_into_image(m, "textures/player.png");
	if (!m->minimap->player)
		free_and_exit(m);
}
