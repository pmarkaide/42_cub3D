/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:20:13 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/04 14:49:16 by pmarkaid         ###   ########.fr       */
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

static int check_first_last_rows(t_macro *macro)
{
	int j = 0;
	char **map = macro->map->map;
	int width = macro->map->w_map;

	while (j < width)
	{
		if (map[0][j] == '0' || map[0][j] == ' ')
			return (0);
		if (map[macro->map->h_map - 1][j] == '0' || map[macro->map->h_map - 1][j] == ' ')
			return (0);
		j++;
	}
	return (1);
}

static int check_edges(char **map, int height)
{
	int i = 1;
	int len;

	while (i < height - 1)
	{
		len = ft_strlen(map[i]);
		if (map[i][0] == '0' || map[i][len - 1] == '0' ||
			map[i][0] == ' ' || map[i][len - 1] == ' ')
			return (0);
		i++;
	}
	return (1);
}

static int check_spaces(char **map, int height)
{
	int i = 1;
	int j;

	while (i < height - 1)
	{
		j = 1;
		while (map[i][j + 1])
		{
			if (map[i][j] == ' ' && (map[i][j - 1] != '1' || map[i][j + 1] != '1'))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static int is_valid_map_structure(t_macro *macro)
{
	char **map = macro->map->map;

	if (!check_first_last_rows(macro))
		return (0);
	if (!check_edges(map, macro->map->h_map))
		return (0);
	if (!check_spaces(map, macro->map->h_map))
		return (0);
	return (1);
}





int validate_map(t_macro *macro)
{
	calculate_map_dimensions(macro);

	if (!map_chars_are_valid(macro))
		return (1);
	if (!is_valid_map_structure(macro))
	{
		ft_printf(2, "Error\nInvalid map structure\n");
		return (1);
	}
	return (0);
}