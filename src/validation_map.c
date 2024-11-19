/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:20:13 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/19 09:19:00 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	check_unique_starting_position(char **grid, size_t height)
{
	size_t	i;
	int		j;
	int		count;
	int		line_length;

	i = 0;
	count = 0;
	while (i < height)
	{
		j = 0;
		line_length = ft_strlen(grid[i]);
		while (j < line_length)
		{
			if (ft_strchr("NSWE", grid[i][j]))
				count++;
			j++;
		}
		i++;
	}
	if (count != 1)
	{
		ft_printf(2, "Error\nMultiple or none starting positions in map\n");
		return (0);
	}
	return (1);
}

static int	map_chars_are_valid(char **grid, size_t height)
{
	size_t	i;
	int		j;
	int		line_length;

	i = 0;
	if (!check_unique_starting_position(grid, height))
		return (0);
	while (i < height)
	{
		j = 0;
		line_length = ft_strlen(grid[i]);
		while (j < line_length)
		{
			if (grid[i][j] && ft_strchr("10NSWE ", grid[i][j]) == NULL)
			{
				ft_printf(2, "Error\nInvalid character in map\n");
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

static int	is_surrounded_by_walls(t_macro *macro, size_t i, size_t j, size_t width)
{
	size_t		height;
	char	**map;
	int		err;

	err = 0;
	height = macro->map->h_map;
	map = macro->map->grid;
	if (i == 0 || j == 0 || i == height - 1 || j == width - 1)
		err = 1;
	if (map[i - 1][j] == ' ' || map[i + 1][j] == ' ')
		err = 1;
	if (map[i][j - 1] == ' ' || map[i][j + 1] == ' ')
		err = 1;
	if (map[i - 1][j - 1] == ' ' || map[i - 1][j + 1] == ' ')
		err = 1;
	if (map[i + 1][j - 1] == ' ' || map[i + 1][j + 1] == ' ')
		err = 1;
	if (err)
	{
		ft_printf(2, "Error\nInvalid map structure at (%d, %d)\n", i, j);
		return (0);
	}
	return (1);
}

static int	is_valid_wall_structure(t_macro *macro)
{
	size_t		i;
	size_t		j;
	char	**map;
	size_t		width;

	i = 0;
	map = macro->map->grid;
	while (i < macro->map->h_map)
	{
		j = 0;
		width = ft_strlen(map[i]);
		while (j < width)
		{
			if (ft_strchr("0NSEW", map[i][j]))
			{
				if (!is_surrounded_by_walls(macro, i, j, width))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	validate_map(t_macro *macro)
{
	calculate_map_dimensions(macro);
	if (!map_chars_are_valid(macro->map->grid, macro->map->h_map))
		return (1);
	if (!is_valid_wall_structure(macro))
		return (1);
	return (0);
}
