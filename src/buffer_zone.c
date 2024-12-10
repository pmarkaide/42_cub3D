/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_zone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 01:58:37 by dbejar-s          #+#    #+#             */
/*   Updated: 2024/12/10 21:28:03 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * Allocates memory for the buffer zone.
 * 
 * @param m Pointer to the macro structure containing map information.
 * @param new_height The height of the new buffer zone.
 * @param new_width The width of the new buffer zone.
 */
static void	allocate_buffer(t_macro *m, int new_height, int new_width)
{
	int	i;

	m->map->buff = (char **)ft_calloc(sizeof(char *), (new_height + 1));
	if (!m->map->buff)
		exit_malloc(m);
	i = 0;
	while (i < new_height)
	{
		m->map->buff[i] = (char *)ft_calloc(sizeof(char), (new_width + 1));
		if (!m->map->buff[i])
			exit_malloc(m);
		i++;
	}
	m->map->buff[new_height] = NULL;
}

/**
 * Initializes the buffer zone with walls ('1') on the edges and empty space ('0') inside.
 * 
 * @param m Pointer to the macro structure containing map information.
 * @param new_height The height of the new buffer zone.
 * @param new_width The width of the new buffer zone.
 */
static void	initialize_buffer(t_macro *m, int new_height, int new_width)
{
	int	i;
	int	j;

	i = 0;
	while (i < new_height)
	{
		j = 0;
		while (j < new_width)
		{
			if (i == 0 || i == new_height - 1 || j == 0 || j == new_width - 1)
				m->map->buff[i][j] = '1';
			else
				m->map->buff[i][j] = '0';
			j++;
		}
		i++;
	}
}

/**
 * Copies the original map into the center of the buffer zone.
 * 
 * @param m Pointer to the macro structure containing map information.
 */
static void	copy_map_to_buffer(t_macro *m)
{
	int	i;
	int	j;

	i = 0;
	while (i < m->map->h_map)
	{
		j = 0;
		while (j < m->map->w_map)
		{
			m->map->buff[i + 6][j + 6] = m->map->grid[i][j];
			j++;
		}
		i++;
	}
}

/**
 * Creates a buffer zone around the original map.
 * 
 * @param m Pointer to the macro structure containing map information.
 */
void	create_buffer_zone(t_macro *m)
{
	m->map->h_buff = m->map->h_map + 12;
	m->map->w_buff = m->map->w_map + 12;
	allocate_buffer(m, m->map->h_buff, m->map->w_buff);
	initialize_buffer(m, m->map->h_buff, m->map->w_buff);
	copy_map_to_buffer(m);
}
