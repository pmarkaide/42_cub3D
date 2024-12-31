/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_map_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 13:21:56 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/12/27 21:29:06 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * Calculates the dimensions of the map.
 * 
 * @param m Pointer to the macro structure containing map information.
 */
void	calculate_map_dimensions(t_macro *m)
{
	int		height;
	int		width;
	int		current_width;
	char	**map;

	height = 0;
	width = 0;
	if (!m->map->grid)
	{
		ft_printf(2, "Error\nMap malloc failed\n");
		free_all(m);
	}
	map = m->map->grid;
	while (map[height])
	{
		current_width = ft_strlen(map[height]);
		if (current_width > width)
			width = current_width;
		height++;
	}
	m->map->w_map = width;
	m->map->h_map = height;
}

/**
 * Fills the map lines with spaces to ensure uniform width.
 * 
 * @param map The map grid.
 * @param width The width of the map.
 * @param m Pointer to the macro structure containing map information.
 */
void	fill_with_spaces(char **map, int width, t_macro *m)
{
	int		i;
	int		len;
	char	*new_line;

	i = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (len < width)
		{
			new_line = malloc(width + 1);
			if (!new_line)
			{
				ft_printf(2, "Error\nMalloc failed\n");
				free_all(m);
			}
			ft_memcpy(new_line, map[i], len);
			ft_memset(new_line + len, ' ', width - len);
			new_line[width] = '\0';
			free(map[i]);
			map[i] = new_line;
		}
		i++;
	}
}

/**
 * Substitutes spaces in the map with zeros.
 * 
 * @param m Pointer to the macro structure containing map information.
 */
void	substitute_spaces_with_zeros(t_macro *m)
{
	int		i;
	int		j;
	char	**grid;
	int		width;

	grid = m->map->grid;
	width = m->map->w_map;
	i = 0;
	while (grid[i] != NULL)
	{
		j = 0;
		while (j < width)
		{
			if (grid[i][j] == ' ')
			{
				grid[i][j] = '0';
			}
			j++;
		}
		i++;
	}
}

/**
 * Checks if there is a unique starting position in the map
 * and store the starting x and y into the macro.
 * 
 * @param m Pointer to the macro structure containing map information.
 * @return The count of starting positions found.
 */
int	check_unique_starting_position(t_macro *m)
{
	int	i;
	int	j;
	int	line_length;
	int	count;

	i = 0;
	count = 0;
	while (i < m->map->h_map)
	{
		line_length = ft_strlen(m->map->grid[i]);
		j = 0;
		while (j < line_length)
		{
			if (ft_strchr("NSWE", m->map->grid[i][j]))
			{
				count++;
				m->map->start_x = j;
				m->map->start_y = i;
				m->map->orientation = m->map->grid[i][j];
			}
			j++;
		}
		i++;
	}
	return (count);
}

/**
 * Validates that all characters in the map are valid.
 * 
 * @param m Pointer to the macro structure containing map information.
 */
void	map_chars_are_valid(t_macro *m)
{
	int	i;
	int	j;
	int	line_length;

	i = 0;
	while (i < m->map->h_map)
	{
		line_length = ft_strlen(m->map->grid[i]);
		j = 0;
		while (j < line_length)
		{
			if (m->map->grid[i][j] && ft_strchr("10NSWE ", m->map->grid[i][j]) == NULL)
			{
				ft_printf(2, "Error\nInvalid character in map\n");
				free_all(m);
			}
			j++;
		}
		i++;
	}
	return ;
}
