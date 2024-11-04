/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:20:13 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/04 15:15:47 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"

static void calculate_map_dimensions(t_macro *macro)
{
	int height = 0;
	int width = 0;
	int current_width;
	char **map = macro->map->map;

	while (map[height])
	{
		current_width = ft_strlen(map[height]);
		if (current_width > width)
			width = current_width;
		height++;
	}
	macro->map->w_map = width;
	macro->map->h_map = height;
}

static int map_chars_are_valid(t_macro *macro)
{
	int i = 0;
	int j;
	int height = macro->map->h_map;
	int width = macro->map->w_map;
	char **map = macro->map->map;

	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			if (map[i][j] && strchr("10NSWE ", map[i][j]) == NULL)
			{
				ft_printf(2, "Error\nInvalid character '%c' in map\n", map[i][j]);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

static int is_surrounded_by_walls(char **map, int i, int j, int height, int width)
{
	if (i == 0 || j == 0 || i == height - 1 || j == width - 1 ||
		map[i - 1][j] == ' ' || map[i + 1][j] == ' ' ||
		map[i][j - 1] == ' ' || map[i][j + 1] == ' ' ||
		map[i - 1][j - 1] == ' ' || map[i - 1][j + 1] == ' ' ||
		map[i + 1][j - 1] == ' ' || map[i + 1][j + 1] == ' ')
	{
		ft_printf(2, "Error\nInvalid map structure at (%d, %d)\n", i, j);
		return (0);
	}
	return (1);
}

static int check_walls(t_macro *macro)
{
	int i = 0;
	int j;
	int height = macro->map->h_map;
	int width = macro->map->w_map;
	char **map = macro->map->map;

	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			if (map[i][j] == '0')
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

static int is_valid_map_structure(t_macro *macro)
{
	if (!check_walls(macro))
		return (0);
	return (1);
}

int validate_map(t_macro *macro)
{
	calculate_map_dimensions(macro);

	if (!map_chars_are_valid(macro))
		return (1);
	if (!is_valid_map_structure(macro))
		return (1);
	return (0);
}