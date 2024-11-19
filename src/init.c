/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:12:51 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/19 13:53:48 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_macro	*init_macro(t_macro *m)
{
	m = malloc(sizeof(t_macro));
	if (!m)
		return (NULL);
	ft_bzero(m, sizeof(t_macro));
	m->map = malloc(sizeof(t_map));
	if (!m->map)
	{
		free(m);
		return (NULL);
	}
	ft_bzero(m->map, sizeof(t_map));
	m->map->no = NULL;
	m->map->so = NULL;
	m->map->we = NULL;
	m->map->ea = NULL;
	m->map->grid = NULL;
	m->images = malloc(sizeof(t_images));
	if (!m->images)
	{
		free(m->map);
		free(m);
		return (NULL);
	}
	ft_bzero(m->images, sizeof(t_images));
	m->images->mini_i = NULL;
	m->images->scene_i = NULL;
	m->images->wall = NULL;
	m->images->background = NULL;
	m->images->player = NULL;
	ft_bzero(&m->keys, sizeof(t_keys));
	ft_bzero(&m->raycast, sizeof(t_raycast));
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
	if (m->images->background)
	{
		mlx_delete_image(m->mlx_cub, m->images->background);
		m->images->background = NULL;
	}
	if (m->images->wall)
	{
		mlx_delete_image(m->mlx_cub, m->images->wall);
		m->images->wall = NULL;
	}
	if (m->images->player)
	{
		mlx_delete_image(m->mlx_cub, m->images->player);
		m->images->player = NULL;
	}
}

void	load_images_into_struct(t_macro *m)
{
	m->images->background = load_png_into_image(m,"textures/background.png");
	if (!m->images->background)
		free_and_exit(m);
	m->images->wall = load_png_into_image(m, "textures/wall.png");
	if (!m->images->wall)
		free_and_exit(m);
	m->images->player = load_png_into_image(m, "textures/player.png");
	if (!m->images->player)
		free_and_exit(m);
}
