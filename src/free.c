/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:10:04 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/12/27 20:24:55 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * Frees the memory allocated for the buffer zone.
 * 
 * @param m Pointer to the macro structure containing map information.
 */
static void	free_buff(t_macro *m)
{
	int	i;

	i = -1;
	if (m->map->buff)
	{
		while (++i < (int)m->map->h_buff)
			free(m->map->buff[i]);
		free(m->map->buff);
		m->map->buff = NULL;
	}
}

/**
 * Frees the memory allocated for the map and its components.
 * 
 * @param m Pointer to the macro structure containing map information.
 */
void	free_map(t_macro *m)
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
			while (m->map->grid[++i])
				free(m->map->grid[i]);
			free(m->map->grid);
			m->map->grid = NULL;
		}
		free_buff(m);
		free(m->map);
		m->map = NULL;
	}
}

/**
 * Frees the memory allocated for the textures.
 * 
 * @param m Pointer to the macro structure containing texture information.
 */
static void	free_textures(t_macro *m)
{
	if (m->tex)
	{
		if (m->tex->no)
			mlx_delete_texture(m->tex->no);
		if (m->tex->so)
			mlx_delete_texture(m->tex->so);
		if (m->tex->we)
			mlx_delete_texture(m->tex->we);
		if (m->tex->ea)
			mlx_delete_texture(m->tex->ea);
		free(m->tex);
	}
}

/**
 * Frees the memory allocated for the macro structure and its components.
 * 
 * @param m Pointer to the macro structure.
 */
void	free_macro(t_macro *m)
{
	if (m)
	{
		free_map(m);
		if (m->ray)
			free(m->ray);
		if (m->keys)
			free(m->keys);
		free_textures(m);
		free(m);
	}
	exit(1);
}

/**
 * Frees all allocated memory and terminates the program.
 * 
 * @param m Pointer to the macro structure.
 */
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
