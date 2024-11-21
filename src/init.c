/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   */
/*   Created: 2024/11/04 12:12:51 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/19 14:40:52 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	initialize_to_zero(t_macro *m)
{
	if (!m)
		return ;
	if (m->map)
		ft_bzero(m->map, sizeof(t_map));
	if (m->images)
		ft_bzero(m->images, sizeof(t_images));
	if (m->ray)
		ft_bzero(m->ray, sizeof(t_ray));
	if (m->keys)
		ft_bzero(m->keys, sizeof(t_keys));
	m->map->no = NULL;
	m->map->so = NULL;
	m->map->we = NULL;
	m->map->ea = NULL;
	m->map->grid = NULL;
	m->images->mini_i = NULL;
	m->images->scene_i = NULL;
	m->images->wall = NULL;
	m->images->background = NULL;
	m->images->player = NULL;
}

static int	malloc_structs(t_macro *m)
{
	m->map = malloc(sizeof(t_map));
	if (!m->map)
		return (0);
	m->images = malloc(sizeof(t_images));
	if (!m->images)
	{
		free(m->map);
		return (0);
	}
	m->ray = malloc(sizeof(t_ray));
	if (!m->ray)
	{
		free(m->images);
		free(m->map);
		return (0);
	}
	m->keys = malloc(sizeof(t_keys));
	if (!m->keys)
	{
		free(m->ray);
		free(m->images);
		free(m->map);
		return (0);
	}
	return (1);
}

t_macro	*init_macro(t_macro *m)
{
	m = malloc(sizeof(t_macro));
	if (!m)
		return (NULL);
	if (!malloc_structs(m))
	{
		free(m);
		return (NULL);
	}
	initialize_to_zero(m);
	return (m);
}

mlx_image_t	*load_png_into_image(t_macro *m, char *file)
{
	mlx_texture_t	*texture;
	mlx_image_t		*img;

	texture = mlx_load_png(file);
	if (!texture)
		free_all(m);
	adjust_image_transparency(texture, 0.5f);
	img = mlx_texture_to_image(m->mlx_cub, texture);
	if (!img)
		free_all(m);
	mlx_delete_texture(texture);
	return (img);
}

void	load_images_into_struct(t_macro *m)
{
	m->images->background = load_png_into_image(m, "textures/background.png");
	if (!m->images->background)
		free_all(m);
	m->images->wall = load_png_into_image(m, "textures/wall.png");
	if (!m->images->wall)
		free_all(m);
	m->images->player = load_png_into_image(m, "textures/player.png");
	if (!m->images->player)
		free_all(m);
}
