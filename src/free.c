/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:10:04 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/19 13:00:37 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
			while (++i < (int)m->map->h_map)
				free(m->map->grid[i]);
			free(m->map->grid);
		}
		free(m->map);
	}
}

void	free_macro(t_macro *m)
{
	free_map(m);
	free(m);
}

void	free_and_exit(t_macro *m)
{
	free_macro(m);
	exit(1);
}
