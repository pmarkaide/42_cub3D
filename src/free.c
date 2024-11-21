/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:10:04 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/21 13:04:42 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	free_map(t_macro *m)
{
	int	i;

	i = -1;
	if (m->map)
	{
		if (m->map->no)
			free(m->map->no);
		if (m->map->so)
			free(m->map->so);
		if (m->map->we)
			free(m->map->we);
		if (m->map->ea)
			free(m->map->ea);
		if (m->map->grid)
		{
			while (++i < (int)m->map->h_map)
				free(m->map->grid[i]);
			free(m->map->grid);
		}
		free(m->map);
		m->map = NULL;
	}
}

static void	free_images(t_macro *m)
{
	if (m->images)
	{
		if (m->images->mini_i)
			mlx_delete_image(m->mlx_cub, m->images->mini_i);
		if (m->images->scene_i)
			mlx_delete_image(m->mlx_cub, m->images->scene_i);
		if (m->images->wall)
			mlx_delete_image(m->mlx_cub, m->images->wall);
		if (m->images->background)
			mlx_delete_image(m->mlx_cub, m->images->background);
		if (m->images->player)
			mlx_delete_image(m->mlx_cub, m->images->player);
		free(m->images);
	}
}

void	free_macro(t_macro *m)
{
	if (m)
	{
		free_map(m);
		free_images(m);
		if (m->ray)
			free(m->ray);
		if (m->keys)
			free(m->keys);
		free(m);
	}
	exit(1);
}

void	free_all(t_macro *m)
{
	if (m)
	{
		if (m->mlx_cub)
		{
			mlx_close_window(m->mlx_cub);
			mlx_terminate(m->mlx_cub);
		}
		free_macro(m);
	}
	exit(1);
}
