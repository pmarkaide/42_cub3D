/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbejar-s <dbejar-s@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:20:13 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/25 22:58:56 by dbejar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	is_surrounded_by_walls(t_macro *m, int i, int j)
{
	int	err;

	err = 0;
	if (i == 0 || j == 0 || i == m->map->h_map - 1 || j == m->map->w_map - 1)
		err = 1;
	else if (m->map->grid[i - 1][j] == ' ' || m->map->grid[i + 1][j] == ' ')
		err = 1;
	else if (m->map->grid[i][j - 1] == ' ' || m->map->grid[i][j + 1] == ' ')
		err = 1;
	else if (m->map->grid[i - 1][j - 1] == ' ' || m->map->grid[i - 1][j
		+ 1] == ' ')
		err = 1;
	else if (m->map->grid[i + 1][j - 1] == ' ' || m->map->grid[i + 1][j
		+ 1] == ' ')
		err = 1;
	if (err)
	{
		ft_printf(2, "Error\nInvalid map structure at (%d, %d)\n", i, j);
		return (0);
	}
	return (1);
}

static void	is_valid_wall_structure(t_macro *m)
{
	int	i;
	int	j;

	i = 0;
	while (i < m->map->h_map)
	{
		j = 0;
		while (j < m->map->w_map)
		{
			if (ft_strchr("0NSEW", m->map->grid[i][j]))
			{
				if (!is_surrounded_by_walls(m, i, j))
					free_macro(m);
			}
			j++;
		}
		i++;
	}
	return ;
}

static void	evaluate_map_islands(t_macro *m)
{
	char	**visited;

	visited = create_visited_array(m->map->h_map, m->map->w_map);
	if (!visited)
	{
		ft_printf(2, "Error\nMalloc failed\n");
		free_macro(m);
	}
	if (check_path(m, visited))
	{
		free_visited_array(visited, m->map->h_map);
		free_macro(m);
	}
	free_visited_array(visited, m->map->h_map);
}

void	validate_map(t_macro *m)
{
	calculate_map_dimensions(m);
	if (m->map->h_map > 500 || m->map->w_map > 500)
	{
		ft_printf(2, "Error\nMap dimensions exceed 500x500\n");
		free_all(m);
	}
	map_chars_are_valid(m);
	if (check_unique_starting_position(m) != 1)
	{
		ft_printf(2, "Error\nMultiple or none starting positions in map\n");
		free_macro(m);
	}
	fill_with_spaces(m->map->grid, m->map->w_map);
	is_valid_wall_structure(m);
	evaluate_map_islands(m);
}
