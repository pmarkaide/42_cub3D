/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbejar-s <dbejar-s@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:10:04 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/26 22:19:41 by dbejar-s         ###   ########.fr       */
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
			while (++i < (int)m->map->h_map - 12)
				free(m->map->grid[i]);
			free(m->map->grid);
		}
		if (m->map->buff)
		{
			i = -1;
			while (++i < (int)m->map->h_map)
				free(m->map->buff[i]);
			free(m->map->buff);
		}
		free(m->map);
		m->map = NULL;
	}
}

static void	free_images(t_macro *m)
{
	if (m->scene_i)
		mlx_delete_image(m->mlx_cub, m->scene_i);
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
