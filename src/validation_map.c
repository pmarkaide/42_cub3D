/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:20:13 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/11/21 14:49:45 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	check_unique_starting_position(t_macro *m)
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

static void	map_chars_are_valid(t_macro *m)
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

static int	is_surrounded_by_walls(t_macro *m, size_t i, size_t j)
{
	int	err;

	err = 0;
	if (i == 0 || j == 0 || i == m->map->h_map - 1 || j == m->map->w_map - 1)
		err = 1;
	if (m->map->grid[i - 1][j] == ' ' || m->map->grid[i + 1][j] == ' ')
		err = 1;
	if (m->map->grid[i][j - 1] == ' ' || m->map->grid[i][j + 1] == ' ')
		err = 1;
	if (m->map->grid[i - 1][j - 1] == ' ' || m->map->grid[i - 1][j + 1] == ' ')
		err = 1;
	if (m->map->grid[i + 1][j - 1] == ' ' || m->map->grid[i + 1][j + 1] == ' ')
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
	size_t	i;
	size_t	j;

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

int	validate_map(t_macro *m)
{
	map_chars_are_valid(m);
	if (check_unique_starting_position(m) != 1)
	{
		ft_printf(2, "Error\nMultiple or none starting positions in map\n");
		free_macro(m);
	}
	is_valid_wall_structure(m);
	return (0);
}
