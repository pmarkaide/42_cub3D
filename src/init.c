/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbejar-s <dbejar-s@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:52:15 by dbejar-s          #+#    #+#             */
/*   Updated: 2024/11/27 01:34:54 by dbejar-s         ###   ########.fr       */
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
	ft_bzero(m->tex, sizeof(t_text));
	m->mlx_cub = NULL;
	m->scene_i = NULL;
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
	m->map->buff = NULL;
	m->scene_i = NULL;
}

static int	malloc_structs(t_macro *m)
{
	m->map = malloc(sizeof(t_map));
	if (!m->map)
		return (0);
	m->ray = malloc(sizeof(t_ray));
	if (!m->ray)
	{
		free(m->map);
		return (0);
	}
	m->keys = malloc(sizeof(t_keys));
	if (!m->keys)
	{
		free(m->ray);
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
		write(2, "Error\nMalloc failed\n", 20);
		free(m);
		return (NULL);
	}
	if (!malloc_structs(m))
	{
		write(2, "Error\nMalloc failed\n", 20);
		free(m->tex);
		free(m);
		return (NULL);
	}
	initialize_to_zero(m);
	return (m);
}
