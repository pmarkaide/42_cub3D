/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:20:13 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/12/30 20:02:29 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * Check that the 0 position is not in touch with a space character
 * in all 8 directions
 *  
 * @param m Pointer to the macro structure containing map information.
 * @param i The x-coordinate of the position.
 * @param j The y-coordinate of the position.
 * @return 1 if the position is surrounded by walls, 0 otherwise.
 */
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

/**
 * Validates that the map is surrounded by walls
 * 
 * @param m Pointer to the macro structure containing map information.
 */
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
					free_all(m);
			}
			j++;
		}
		i++;
	}
	return ;
}

/**
 * Evaluates the map for isolated areas (islands).
 * 
 * @param m Pointer to the macro structure containing map information.
 */
static void	evaluate_map_islands(t_macro *m)
{
	char	**visited;

	visited = create_visited_array(m->map->h_map, m->map->w_map);
	if (!visited)
	{
		ft_printf(2, "Error\nMalloc failed\n");
		free_all(m);
	}
	if (check_islands(m, visited))
	{
		free_visited_array(visited, m->map->h_map);
		free_all(m);
	}
	free_visited_array(visited, m->map->h_map);
}

/**
 * Validates the map correctness:
 * 
 * Dimensions, characters, starting position, wall structure, and islands.
 * 
 * @param m Pointer to the macro structure containing map information.
 */
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
		free_all(m);
	}
	fill_with_spaces(m->map->grid, m->map->w_map, m);
	is_valid_wall_structure(m);
	evaluate_map_islands(m);
}
