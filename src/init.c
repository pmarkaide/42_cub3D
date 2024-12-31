/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:52:15 by dbejar-s          #+#    #+#             */
/*   Updated: 2024/12/27 20:27:52 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * Initializes all components of the macro structure
 * 
 * @param m Pointer to the macro structure.
 */
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

/**
 * Allocates memory for the map, ray, and keys structures.
 * 
 * @param m Pointer to the macro structure.
 * @return 1 if memory allocation is successful, 0 otherwise.
 */
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

/**
 * Initializes the macro structure and its components.
 * 
 * @param m Pointer to the macro structure.
 * @return A pointer to the initialized macro structure, or NULL if memory allocation fails.
 */
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
