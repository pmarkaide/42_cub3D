/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_map_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 13:21:56 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/24 13:37:32 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
		free_macro(m);
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

void	fill_with_spaces(char **map, size_t width)
{
	size_t	i;
	size_t	len;
	char	*new_line;

	i = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (len < width)
		{
			new_line = malloc(width + 1);
			if (!new_line)
				return ;
			ft_memcpy(new_line, map[i], len);
			ft_memset(new_line + len, ' ', width - len);
			new_line[width] = '\0';
			free(map[i]);
			map[i] = new_line;
		}
		i++;
	}
}

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

int	check_unique_starting_position(t_macro *m)
{
	size_t	i;
	size_t	j;
	int		count;

	i = 0;
	count = 0;
	while (i < m->map->h_map)
	{
		j = 0;
		while (j < m->map->w_map)
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

void	map_chars_are_valid(t_macro *m)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < m->map->h_map)
	{
		j = 0;
		while (j < m->map->w_map)
		{
			if (m->map->grid[i][j] && ft_strchr("10NSWE ",
					m->map->grid[i][j]) == NULL)
			{
				ft_printf(2, "Error\nInvalid character in map\n");
				free_macro(m);
			}
			j++;
		}
		i++;
	}
	return ;
}
