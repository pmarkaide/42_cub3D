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
	int	i;

	i = -1;
	ft_bzero(m->map, sizeof(t_map));
	ft_bzero(m->ray, sizeof(t_ray));
	ft_bzero(m->keys, sizeof(t_keys));
	m->map->no = NULL;
	m->map->so = NULL;
	m->map->we = NULL;
	m->map->ea = NULL;
	while (++i < 3)
	{
		m->map->f[i] = -1;
		m->map->c[i] = -1;
	}
	m->map->grid = NULL;
	m->scene_i = NULL;
}

static int	malloc_structs(t_macro *m)
{
	m->map = malloc(sizeof(t_map));
	if (!m->map)
		return (0);
	m->scene_i = malloc(sizeof(mlx_image_t));
	if (!m->scene_i)
	{
		free(m->map);
		return (0);
	}
	m->ray = malloc(sizeof(t_ray));
	if (!m->ray)
	{
		free(m->scene_i);
		free(m->map);
		return (0);
	}
	m->keys = malloc(sizeof(t_keys));
	if (!m->keys)
	{
		free(m->ray);
		free(m->scene_i);
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
	m->tex = malloc(sizeof(t_text));
	if (!m->tex)
	{
		free(m);
		return (NULL);
	}
	if (!malloc_structs(m))
	{
		free(m->tex);
		free(m);
		return (NULL);
	}
	initialize_to_zero(m);
	return (m);
}
