/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_zone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbejar-s <dbejar-s@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 01:58:37 by dbejar-s          #+#    #+#             */
/*   Updated: 2024/11/27 09:34:44 by dbejar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

void	create_buffer_zone(t_macro *m)
{
	m->map->h_buff = m->map->h_map + 12;
	m->map->w_buff = m->map->w_map + 12;
	allocate_buffer(m, m->map->h_buff, m->map->w_buff);
	initialize_buffer(m, m->map->h_buff, m->map->w_buff);
	copy_map_to_buffer(m);
}
