/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbejar-s <dbejar-s@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:05:47 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/25 14:13:14 by dbejar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	print_map_struct(t_map *map)
{
	int	i;

	printf("Textures:\n");
	printf("  NO: %s\n", map->no);
	printf("  SO: %s\n", map->so);
	printf("  WE: %s\n", map->we);
	printf("  EA: %s\n", map->ea);
	printf("\nFloor Colors (RGB):\n");
	printf("  F: %d, %d, %d\n", map->f[0], map->f[1], map->f[2]);
	printf("\nCeiling Colors (RGB):\n");
	printf("  C: %d, %d, %d\n", map->c[0], map->c[1], map->c[2]);
	printf("\nMap Dimensions:\n");
	printf("  Width: %d\n", map->w_map);
	printf("  Height: %d\n", map->h_map);
	printf("\nMap Layout:\n");
	i = 0;
	while (map->grid[i])
	{
		printf("  %s\n", map->grid[i]);
		i++;
	}
	printf("\n");
}

void	print_arrays(t_macro *m, char **visited)
{
	int	i;
	int	j;

	ft_printf(1, "Grid:\n");
	for (i = 0; i < m->map->h_map; i++)
	{
		for (j = 0; j < m->map->w_map; j++)
			ft_printf(1, "%c ", m->map->grid[i][j]);
		ft_printf(1, "\n");
	}
	ft_printf(1, "\nVisited:\n");
	for (i = 0; i < m->map->h_map; i++)
	{
		for (j = 0; j < m->map->w_map; j++)
			ft_printf(1, "%d ", visited[i][j]);
		ft_printf(1, "\n");
	}
}
