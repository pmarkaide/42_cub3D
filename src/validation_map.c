/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:20:13 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/04 16:19:21 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	check_unique_starting_position(t_macro *macro)
{
	int		i;
	int		j;
	int		count;
	char	**map;
	int		line_length;

	i = 0;
	count = 0;
	map = macro->map->map;
	while (i < macro->map->h_map)
	{
		j = 0;
		line_length = ft_strlen(map[i]);
		while (j < line_length)
		{
			if (ft_strchr("NSWE", map[i][j]))
			{
				ft_printf(2, "Starting position: %c at (%d, %d)\n", map[i][j],
					i, j);
				count++;
			}
			if (count > 1)
			{
				ft_printf(2, "Error\nMultiple starting positions in map\n");
				return (0);
			}
			j++;
		}
		i++;
	}
	return (count == 1);
}

static int	map_chars_are_valid(t_macro *macro)
{
	int		i;
	int		j;
	char	**map;

	i = 0;
	map = macro->map->map;
	if (!check_unique_starting_position(macro))
		return (0);
	while (i < macro->map->h_map)
	{
		j = 0;
		while (j < macro->map->w_map)
		{
			if (map[i][j] && ft_strchr("10NSWE ", map[i][j]) == NULL)
			{
				ft_printf(2, "Error\nInvalid character '%c' in map\n",
					map[i][j]);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

static int	is_surrounded_by_walls(char **map, int i, int j, int height,
		int width)
{
	if (i == 0 || j == 0 || i == height - 1 || j == width - 1 || map[i
		- 1][j] == ' ' || map[i + 1][j] == ' ' || map[i][j - 1] == ' '
		|| map[i][j + 1] == ' ' || map[i - 1][j - 1] == ' ' || map[i - 1][j
		+ 1] == ' ' || map[i + 1][j - 1] == ' ' || map[i + 1][j + 1] == ' ')
	{
		ft_printf(2, "Error\nInvalid map structure at (%d, %d)\n", i, j);
		return (0);
	}
	return (1);
}

static int	is_valid_wall_structure(t_macro *macro)
{
	int		i;
	int		j;
	int		height;
	char	**map;
	int		width;

	i = 0;
	height = macro->map->h_map;
	map = macro->map->map;
	while (i < height)
	{
		j = 0;
		width = ft_strlen(map[i]);
		while (j < width)
		{
			if (ft_strchr("0NSEW", map[i][j]))
			{
				if (!is_surrounded_by_walls(map, i, j, height, width))
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
	if (!map_chars_are_valid(macro))
		return (1);
	if (!is_valid_wall_structure(macro))
		return (1);
	return (0);
}
